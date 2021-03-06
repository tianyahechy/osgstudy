//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_NODE
#define OSG_NODE 1

#include <osg/Object.h>
#include <osg/StateSet.h>
#include <osg/BoundingSphere.h>
#include <osg/NodeCallback.h>

#include <string>
#include <vector>

namespace osg {

class NodeVisitor;
class Group;

/** META_Node macro define the standard clone, isSameKindAs, className
  * and accept methods.  Use when subclassing from Node to make it
  * more convinient to define the required pure virtual methods.*/
#define META_Node(library,name) \
        virtual osg::Object* cloneType() const { return osgNew name (); } \
        virtual osg::Object* clone(const osg::CopyOp& copyop) const { return osgNew name (*this,copyop); } \
        virtual bool isSameKindAs(const osg::Object* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
        virtual const char* className() const { return #name; } \
        virtual const char* libraryName() const { return #library; } \
        virtual void accept(osg::NodeVisitor& nv) { if (nv.validNodeMask(*this)) { nv.pushOntoNodePath(this); nv.apply(*this); nv.popFromNodePath(); } } \
        

/** Base class for all internal nodes in the scene graph.
    Provides interface for most common node operations (Composite Pattern).
*/
class SG_EXPORT Node : public Object
{
    public:

        /** Construct a node.
            Initialize the parent list to empty, node name to "" and 
            bounding sphere dirty flag to true.*/
        Node();

        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Node(const Node&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        /** clone the an object of the same type as the node.*/
        virtual Object* cloneType() const { return osgNew Node(); }

        /** return a clone of a node, with Object* return type.*/
        virtual Object* clone(const CopyOp& copyop) const { return osgNew Node(*this,copyop); }

        /** return true if this and obj are of the same kind of object.*/
        virtual bool isSameKindAs(const Object* obj) const { return dynamic_cast<const Node*>(obj)!=NULL; }

        /** return the name of the node's library.*/
        virtual const char* libraryName() const { return "osg"; }

        /** return the name of the node's class type.*/
        virtual const char* className() const { return "Node"; }

        /** Visitor Pattern : calls the apply method of a NodeVisitor with this node's type.*/
        virtual void accept(NodeVisitor& nv);
        /** Traverse upwards : calls parents' accept method with NodeVisitor.*/
        virtual void ascend(NodeVisitor& nv);
        /** Traverse downwards : calls children's accept method with NodeVisitor.*/
        virtual void traverse(NodeVisitor& /*nv*/) {}


        /** Set the name of node using C++ style string.*/
        inline void setName( const std::string& name ) { _name = name; }
        /** Set the name of node using a C style string.*/
        inline void setName( const char* name ) { _name = name; }
        /** Get the name of node.*/
        inline const std::string& getName() const { return _name; }
        

        /** A vector of osg::Group pointers which is used to store the parent(s) of node.*/
        typedef std::vector<Group*> ParentList;

        /** Get the parent list of node. */
        inline const ParentList& getParents() const { return _parents; }

        /** Get the a copy of parent list of node. A copy is returned to 
          * prevent modification of the parent list.*/
        inline ParentList getParents() { return _parents; }

        inline Group* getParent(const unsigned int i)  { return _parents[i]; }
        /**
         * Get a single const parent of node.
         * @param i index of the parent to get.
         * @return the parent i.
         */
        inline const Group* getParent(const unsigned int i) const  { return _parents[i]; }

        /**
         * Get the number of parents of node.
         * @return the number of parents of this node.
         */
        inline const unsigned int getNumParents() const { return _parents.size(); }


        /** Set app node callback, called during app traversal. */
        void setAppCallback(NodeCallback* nc);

        /** Get app node callback, called during app traversal. */
        inline NodeCallback* getAppCallback() { return _appCallback.get(); }

        /** Get const app node callback, called during app traversal. */
        inline const NodeCallback* getAppCallback() const { return _appCallback.get(); }

        /** Get the number of Children of this node which require App traversal,
          * since they have an AppCallback attached to them or their children.*/
        inline const int getNumChildrenRequiringAppTraversal() const { return _numChildrenRequiringAppTraversal; }


        /** Set cull node callback, called during cull traversal. */
        void setCullCallback(NodeCallback* nc) { _cullCallback = nc; }

        /** Get app node callback, called during app traversal. */
        inline NodeCallback* getCullCallback() { return _cullCallback.get(); }

        /** Get const app node callback, called during app traversal. */
        inline const NodeCallback* getCullCallback() const { return _cullCallback.get(); }

        /** Set the view frustum/small feature culling of this node to be active or inactive.
          * The default value to true for _cullingActive. Used a guide
          * to the cull traversal.*/
        void setCullingActive(const bool active);

        /** Get the view frustum/small feature _cullingActive flag for this node. Used a guide
          * to the cull traversal.*/
        inline const bool getCullingActive() const { return _cullingActive; }

        /** Get the number of Children of this node which have culling disabled.*/
        inline const int getNumChildrenWithCullingDisabled() const { return _numChildrenWithCullingDisabled; }

        /** Return true if this node can be culled by view frustum, occlusion or small feature culling during the cull traversal.
          * note, return true only if no children have culling disabled, and the local _cullingActive flag is true.*/
        inline const bool isCullingActive() const { return _numChildrenWithCullingDisabled==0 && _cullingActive && _bsphere.valid(); }

        /** Get the number of Children of this node which are or have OccluderNode's.*/
        inline const int getNumChildrenWithOccluderNodes() const { return _numChildrenWithOccluderNodes; }

        
        /** return true if this node is an OccluderNode or the subgraph below this node are OccluderNodes.*/
        const bool containsOccluderNodes() const;


        typedef unsigned int NodeMask;
        /** Set the node mask. Note, node mask is will be replaced by TraversalMask.*/
        inline void setNodeMask(const NodeMask nm) { _nodeMask = nm; }
        /** Get the node Mask. Note, node mask is will be replaced by TraversalMask.*/
        inline const NodeMask getNodeMask() const { return _nodeMask; }



        /** A vector of std::string's which are used to describe the object.*/
        typedef std::vector<std::string> DescriptionList;

        /** Get the description list of the const node.*/        
        inline const DescriptionList& getDescriptions() const { return _descriptions; }
        /** Get the description list of the const node.*/        
        inline DescriptionList& getDescriptions() { return _descriptions; }
        /** Get a single const description of the const node.*/
        inline const std::string& getDescription(const int i) const { return _descriptions[i]; }
        /** Get a single description of the node.*/
        inline std::string& getDescription(const int i) { return _descriptions[i]; }
        /** Get the number of descriptions of the node.*/
        inline const int getNumDescriptions() const { return _descriptions.size(); }
        /** Add a description string to the node.*/
        void addDescription(const std::string& desc) { _descriptions.push_back(desc); }


        /** set the node's StateSet.*/
        inline void setStateSet(osg::StateSet* dstate) { _dstate = dstate; }

        /** return the node's StateSet, if one does not already exist create it
          * set the node and return the newly created StateSet. This ensures
          * that a valid StateSet is always returned and can be used directly.*/
        osg::StateSet* getValidStateSet();

        /** return the node's StateSet. returns NULL if a stateset is not attached.*/
        inline osg::StateSet* getStateSet() { return _dstate.get(); }

        /** return the node's const StateSet. returns NULL if a stateset is not attached.*/
        inline const osg::StateSet* getStateSet() const { return _dstate.get(); }

        /** get the bounding sphere of node.
           Using lazy evaluation computes the bounding sphere if it is 'dirty'.*/
        inline const BoundingSphere& getBound() const
        {
            if(!_bsphere_computed) computeBound();
            return _bsphere;
        }


        /** Mark this node's bounding sphere dirty.
            Forcing it to be computed on the next call to getBound().*/
        void dirtyBound();


    protected:

        /** Node destructor. Note, is protected so that Nodes cannot
            be deleted other than by being dereferenced and the reference
            count being zero (see osg::Referenced), preventing the deletion
            of nodes which are still in use. This also means that
            Node's cannot be created on stack i.e Node node will not compile,
            forcing all nodes to be created on the heap i.e Node* node
            = new Node().*/
        virtual ~Node();


        /** Compute the bounding sphere around Node's geometry or children.
            This method is automatically called by getBound() when the bounding
            sphere has been marked dirty via dirtyBound().*/
        virtual const bool computeBound() const;

        mutable BoundingSphere _bsphere;
        mutable bool _bsphere_computed;

        std::string _name;

        void addParent(osg::Group* node);
        void removeParent(osg::Group* node);

        ParentList _parents;
        friend class osg::Group;
        friend class osg::Drawable;

        ref_ptr<NodeCallback> _appCallback;
        int _numChildrenRequiringAppTraversal;
        void setNumChildrenRequiringAppTraversal(const int num);

        ref_ptr<NodeCallback> _cullCallback;

        bool _cullingActive;
        int _numChildrenWithCullingDisabled;        
        void setNumChildrenWithCullingDisabled(const int num);

        int _numChildrenWithOccluderNodes;        
        void setNumChildrenWithOccluderNodes(const int num);

        NodeMask _nodeMask;
        
        DescriptionList _descriptions;

        ref_ptr<StateSet> _dstate;

};

/** A vector of Nodes pointers which is used to describe the path from a root node to a descendant.*/
typedef std::vector<Node*> NodePath;

}

#endif
