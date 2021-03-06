//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_NODEVISITOR
#define OSG_NODEVISITOR 1

#include <osg/Node.h>
#include <osg/Matrix.h>
#include <osg/FrameStamp.h>

namespace osg {

class Geode;
class Billboard;
class LightSource;
class ClipNode;
class Group;
class Transform;
class Projection;
class LOD;
class Switch;
class Impostor;
class EarthSky;
class OccluderNode;

/** Visitor for type safe operations on osg::Node's.
    Based on GOF's Visitor pattern. The NodeVisitor 
    is useful for developing type safe operations to nodes
    in the scene graph (as per Visitor pattern), and adds to this
    support for optional scene graph traversal to allow
    operations to be applied to whole scenes at once. The Visitor
    pattern uses a technique of double dispatch as a mechanism to
    called the appropriate apply(..) method of the NodeVisitor.  To
    use this feature one must use the Node::accept(NodeVisitor) which
    is extended in each Node subclass, rather than the NodeVisitor
    apply directly.  So use root->accept(myVisitor); instead of
    myVisitor.apply(*root).  The later method will bypass the double
    dispatch and the appropriate NodeVisitor::apply(..) method will
    not be called. */ 
class SG_EXPORT NodeVisitor : public Referenced
{
    public:

        enum TraversalMode {
            TRAVERSE_NONE,
            TRAVERSE_PARENTS,
            TRAVERSE_ALL_CHILDREN,
            TRAVERSE_ACTIVE_CHILDREN,
            TRAVERSE_VISITOR
        };

        NodeVisitor(TraversalMode tm=TRAVERSE_NONE);
        virtual ~NodeVisitor();

        /** Method to call to reset visitor. Useful for your visitor accumulates
            state during a traversal, and you plan to reuse the visitor. 
            To flush that state for the next traversal than call reset() prior
            to each traversal.*/
        virtual void reset() {}


        /** Set the traversal number. Typically used to denote the frame count.*/
        inline void setTraversalNumber(const int fn) { _traversalNumber = fn; }
        
        /** Get the traversal number. Typically used to denote the frame count.*/
        inline const int getTraversalNumber() const { return _traversalNumber; }

        /** Set the FrameStamp that this traversal is assoicated with.*/
        inline void setFrameStamp(FrameStamp* fs) { _frameStamp = fs; }
        
        /** Get the FrameStamp that this traversal is assoicated with.*/
        inline const FrameStamp* getFrameStamp() const { return _frameStamp.get(); }


        /** Set the TraversalMask of this NodeVisitor.
          * The TraversalMask is used by the NodeVisitor::validNodeMask() method
          * to determine whether to operate on a node and its subgraph.
          * validNodeMask() is called automaticaly in the Node::accept() method before
          * any call to NodeVisitor::apply(), apply() is only ever called if validNodeMask
          * returns true. Note, if NodeVisitor::_traversalMask is 0 then all operations
          * will be swithced off for all nodes.  Whereas setting both _traversalMask and
          * _nodeMaskOverride to 0xffffffff will allow a visitor to work on all nodes
          * regardless of their own Node::_nodeMask state.*/
        inline void setTraversalMask(const Node::NodeMask mask) { _traversalMask = mask; }

        /** Get the TraversalMask.*/
        inline const Node::NodeMask getTraversalMask() const { return _traversalMask; }

        /** Set the NodeMaskOverride mask.
          * Used in validNodeMask() to determine whether to operate on a node or its 
          * subgraph, by OR'ing NodeVisitor::_nodeMaskOverride with the Node's own Node::_nodeMask.
          * Typically used to force on nodes which may have
          * been switched off by their own Node::_nodeMask.*/
        inline void setNodeMaskOverride(const Node::NodeMask mask) { _nodeMaskOverride = mask; }

        /** Get the NodeMaskOverride mask.*/
        inline const Node::NodeMask getNodeMaskOverride() const { return _nodeMaskOverride; }
        
        /** Method to called by Node and its subclass' Node::accept() method, if the result is true
          * to be used to cull operations of nodes and their subgraphs.
          * Return true if the result of a bit wise and of the NodeVisitor::_traversalMask
          * with the bit or between NodeVistor::_nodeMaskOverride and the Node::_nodeMask.
          * default values for _traversalMask is 0xffffffff, _nodeMaskOverride is 0x0,
          * and osg::Node::_nodeMask is 0xffffffff. */
        inline const bool validNodeMask(const osg::Node& node) const
        {
            return (getTraversalMask() & (getNodeMaskOverride() | node.getNodeMask()))!=0;
        }

        /** Set the traversal mode for Node::traverse() to use when 
            deciding which children of a node to traverse. If a
            NodeVisitor has been attached via setTraverseVisitor()
            and the new mode is not TRAVERSE_VISITOR then the attached
            visitor is detached. Default mode is TRAVERSE_NONE.*/
        void setTraversalMode(const TraversalMode mode);
        
        /** Get the traversal mode.*/
        inline const TraversalMode getTraversalMode() const { return _traversalMode; }

        /** Set a visitor to handle traversal.
            Overrides the traverse mode setting it to TRAVERSAL_VISITOR.*/
        void setTraversalVisitor(NodeVisitor* nv);
        
        /** Get the traversal visitor, returns NULL if none is attached.*/
        inline NodeVisitor* getTraversalVisitor() { return _traversalVisitor.get(); }

        /** Method for handling traversal of a nodes.
            If you intend to use the visitor for actively traversing 
            the scene graph then make sure the accept() methods call
            this method unless they handle traversal directly.*/
        inline void traverse(Node& node)
        {
            if (_traversalVisitor.valid()) node.accept(*_traversalVisitor);
            else if (_traversalMode==TRAVERSE_PARENTS) node.ascend(*this);
            else if (_traversalMode!=TRAVERSE_NONE) node.traverse(*this);
        }
        
        /** Method called by osg::Node::accept() method before
          * a call the NodeVisitor::apply(..).  The back of the list will,
          * therefore, be the current node being visited inside the apply(..),
          * and the rest of the list will be the parental sequence of nodes 
          * from the top most node applied down the graph to the current node.
          * Note, the user does not typically call pushNodeOnPath() as it
          * will be called automatically by the Node::accept() method.*/
        inline void pushOntoNodePath(Node* node) { _nodePath.push_back(node); }
        
        /** Method callby osg::Node::accept() method after
          * a call the NodeVisitor::apply(..).
          * Note, the user does not typically call pushNodeOnPath() as it
          * will be called automatically by the Node::accept() method.*/
        inline void popFromNodePath()            { _nodePath.pop_back(); }
        
        /** Get the non const NodePath from the top most node applied down
          * to the current Node being visited.*/
        NodePath& getNodePath() { return _nodePath; }

        /** Get the const NodePath from the top most node applied down
          * to the current Node being visited.*/
        const NodePath& getNodePath() const { return _nodePath; }
        
        /** Get the Local To World Matrix from the NodePath for specified Transform::Mode, and u.*/
        const bool getLocalToWorldMatrix(Matrix& matrix, Node* node);
        
        /** Get the World To Local Matrix from the NodePath for specified Transform::Mode.*/
        const bool getWorldToLocalMatrix(Matrix& matrix, Node* node);


        virtual void apply(Node& node)          { traverse(node);}
        
        virtual void apply(Geode& node)         { apply((Node&)node); }
        virtual void apply(Billboard& node)     { apply((Geode&)node); }
        virtual void apply(LightSource& node)   { apply((Node&)node); }
        virtual void apply(ClipNode& node)      { apply((Node&)node); }
        
        virtual void apply(Group& node)         { apply((Node&)node); }
        virtual void apply(Projection& node)    { apply((Group&)node); }
        virtual void apply(Transform& node)     { apply((Group&)node); }
        virtual void apply(Switch& node)        { apply((Group&)node); }
        virtual void apply(LOD& node)           { apply((Group&)node); }
        virtual void apply(Impostor& node)      { apply((LOD&)node); }
        virtual void apply(EarthSky& node)      { apply((Group&)node); }
        virtual void apply(OccluderNode& node)  { apply((Group&)node); }


    protected:

        int                     _traversalNumber;
        
        ref_ptr<FrameStamp>     _frameStamp;

        ref_ptr<NodeVisitor>    _traversalVisitor;
        
        TraversalMode           _traversalMode;
        Node::NodeMask          _traversalMask;
        Node::NodeMask          _nodeMaskOverride;
        
        NodePath                _nodePath;

};


/** Convenience functor for assisting visiting of arrays of osg::Node's.*/ 
struct NodeAcceptOp
{
    NodeVisitor& _nv;
    NodeAcceptOp(NodeVisitor& nv):_nv(nv) {}
    void operator () (Node* node) { node->accept(_nv); }
    void operator () (ref_ptr<Node> node) { node->accept(_nv); }
};

}

#endif
