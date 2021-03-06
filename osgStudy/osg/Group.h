//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_GROUP
#define OSG_GROUP 1

#include <osg/Node.h>
#include <osg/NodeVisitor.h>

namespace osg {

/** General group node which maintains a list of children.
    Children are reference counted. This allows children to be shared
    with memory management handled automatically via osg::Referenced.
*/
class SG_EXPORT Group : public Node
{
    public :

        typedef std::vector<ref_ptr<Node> > ChildList;

        Group();
        
        /** Copy constructor using CopyOp to manage deep vs shallow copy.*/
        Group(const Group&,const CopyOp& copyop=CopyOp::SHALLOW_COPY);

        META_Node(osg, Group);

        virtual void traverse(NodeVisitor& nv);

        /** Add Node to Group.
         *  If node is not NULL and is not contained in Group then increment its  
         *  reference count, add it to the child list and dirty the bounding 
         *  sphere to force it to recompute on next getBound() and return true for success.
         *  Otherwise return false. Scene nodes can't be added as child nodes.
         */
        virtual bool addChild( Node *child );

        /** Remove Node from Group.
         *  If Node is contained in Group then remove it from the child
         *  list, decrement its reference count, and dirty the 
         *  bounding sphere to force it to recompute on next getBound() and
         *  return true for success.  If Node is not found then return false
         *  and do not change the reference count of the Node.
         */
        virtual bool removeChild( Node *child );

        /** Replace specified Node with another Node.
         *  Decrement the reference count origNode and increments the
         *  reference count of newNode, and dirty the bounding sphere
         *  to force it to recompute on next getBound() and returns true.
         *  If origNode is not found then return false and do not 
         *  add newNode.  If newNode is NULL then return false and do
         *  not remove origNode. Also returns false if newChild is a Scene node.
         */
        virtual bool replaceChild( Node *origChild, Node* newChild );

        /** return the number of chilren nodes.*/
        inline const unsigned  int getNumChildren() const { return _children.size(); }

        /** return child node at position i.*/
        inline Node *getChild( const unsigned  int i ) { return _children[i].get(); }

        /** return child node at position i.*/
        inline const Node *getChild( const unsigned  int i ) const { return _children[i].get(); }

        /** return true if node is contained within Group.*/
        inline bool containsNode( const Node* node ) const
        {
            
            for (ChildList::const_iterator itr=_children.begin();
                 itr!=_children.end();
                 ++itr)
            {
                if (itr->get()==node) return true;
            }
            return false;
        }


        /** return the iterator position for specified Node.
         *  return _children.end() if node is not contained in Group.
         */
        inline ChildList::iterator findNode( const Node* node )
        {
            for (ChildList::iterator itr=_children.begin();
                 itr!=_children.end();
                 ++itr)
            {
                if (itr->get()==node) return itr;
            }
            return _children.end();
        }

        /** return the const_iterator position for specified Node.
         *  return _children.end() if node is not contained in Group.
         */
        inline ChildList::const_iterator findNode( const Node* node ) const
        {
            for (ChildList::const_iterator itr=_children.begin();
                 itr!=_children.end();
                 ++itr)
            {
                if (itr->get()==node) return itr;
            }
            return _children.end();
        }

    protected:

        virtual ~Group();

        virtual const bool computeBound() const;

        ChildList _children;


};

}

#endif
