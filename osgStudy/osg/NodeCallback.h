//C++ header - Open Scene Graph - Copyright (C) 1998-2002 Robert Osfield
//Distributed under the terms of the GNU Library General Public License (LGPL)
//as published by the Free Software Foundation.

#ifndef OSG_NODECALLBACK
#define OSG_NODECALLBACK 1

#include <osg/Referenced.h>
#include <osg/ref_ptr.h>

namespace osg {

class Node;
class NodeVisitor;

class SG_EXPORT NodeCallback : public Referenced {

    public :
    

        NodeCallback(){}
        virtual ~NodeCallback() {}
        
        
        /** Callback method call by the NodeVisitor when visiting a node.*/
        virtual void operator()(Node* node, NodeVisitor* nv)
        { 
            // note, callback is repsonsible for scenegraph traversal so
            // should always include call the traverse(node,nv) to ensure 
            // that the rest of cullbacks and the scene graph are traversed.
            traverse(node,nv);
        }
        
        /** Call any nested callbacks and then traverse the scene graph. */
        void traverse(Node* node,NodeVisitor* nv);
        
        void setNestedCallback(NodeCallback* nc) { _nestedCallback = nc; }
        NodeCallback* getNestedCallback() { return _nestedCallback.get(); }
        
        inline void addNestedCallback(NodeCallback* nc)
        {
            if (nc)
            {
                if (_nestedCallback.valid())
                {
                    nc->addNestedCallback(_nestedCallback.get());
                    _nestedCallback = nc;
                }
                else
                {
                    _nestedCallback = nc;
                }
            }
        }
        
        inline void removeNestedCallback(NodeCallback* nc)
        {
            if (nc)
            {
                if (_nestedCallback==nc)
                {
                    NodeCallback* nested_nc = _nestedCallback->getNestedCallback();
                    if (nested_nc) _nestedCallback = nc;
                    else _nestedCallback = 0;
                }
                else
                {
                    _nestedCallback->removeNestedCallback(nc);
                }
            }
        }
        
   public:

        ref_ptr<NodeCallback> _nestedCallback;
};

} // namespace

#endif

