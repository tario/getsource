/*

This file is part of the getsource project, http://github.com/tario/getsource

Copyright (c) 2009-2010 Roberto Dario Seminara <robertodarioseminara@gmail.com>

getsource is free software: you can redistribute it and/or modify
it under the terms of the gnu general public license as published by
the free software foundation, either version 3 of the license, or
(at your option) any later version.

getsource is distributed in the hope that it will be useful,
but without any warranty; without even the implied warranty of
merchantability or fitness for a particular purpose.  see the
gnu general public license for more details.

you should have received a copy of the gnu general public license
along with getsource.  if not, see <http://www.gnu.org/licenses/>.

*/

#include <ruby.h>
#ifdef RUBY1_8

#include <node.h>

struct METHOD {
    VALUE klass, rklass;

    VALUE recv;
    ID id, oid;
    int safe_level;
    NODE *body;
};
unsigned char* base__;

#define nd_file(n) n->nd_file
#include <dlfcn.h>

VALUE rb_cNode;
ID intern_owner;
ID intern_name;
ID intern_sym;

typedef VALUE (*MNEW)(VALUE klass, VALUE obj, ID id, VALUE mclass, int scope);
MNEW mnew_;
unsigned char* base__;

/*
	The node that acts as body of the method
*/
VALUE rb_method_body(VALUE self) {

//	VALUE name = rb_funcall(self, intern_name, 0);
//	VALUE sym = rb_funcall(name, intern_sym, 0);
//	VALUE owner = rb_funcall(self, intern_owner, 0);
//	NODE* body = rb_method_node(owner, SYM2ID(sym) );

	struct METHOD* method;
	Data_Get_Struct(self,struct METHOD,method);

	if (method->body == 0) return Qnil;

	// nd_defn is only present in ruby_1.8
	if (method->body->nd_defn != 0) {
		return Data_Wrap_Struct(rb_cNode, 0, 0, method->body->nd_defn);
	}

	return Data_Wrap_Struct(rb_cNode, 0, 0, method->body);
}

/*
The number of the line where the code associated with note are defined in the ruby source file
*/
VALUE rb_node_line(VALUE self) {
    NODE* _node;
    Data_Get_Struct(self,NODE,_node);

    return INT2FIX(nd_line(_node));

}


/*
The name of the ruby source file where the code associated with the node are defined
*/
VALUE rb_node_file(VALUE self) {
    NODE* _node;
    Data_Get_Struct(self,NODE,_node);

    if (nd_file(_node)  == NULL ) {
	    return rb_str_new2("");
    }
    return rb_str_new2(nd_file(_node) );
}


static void
bm_mark(struct METHOD *data)
{
    rb_gc_mark(data->klass);
    rb_gc_mark(data->rklass);
    rb_gc_mark(data->recv);
    rb_gc_mark((VALUE)data->body);
}

static VALUE
umethod_unchecked_bind(VALUE method, VALUE recv)
{
    struct METHOD *data, *bound;

    Data_Get_Struct(method, struct METHOD, data);

    method = Data_Make_Struct(rb_cMethod, struct METHOD, bm_mark, -1, bound);
    *bound = *data;
    bound->recv = recv;
    bound->rklass = CLASS_OF(recv);

    return method;
}


void  Init_getsource_base() {
	rb_define_method(rb_cMethod, "body", rb_method_body,0);
	rb_define_method(rb_cUnboundMethod, "body", rb_method_body,0);
	rb_define_method(rb_cUnboundMethod, "unchecked_bind", umethod_unchecked_bind,1);

	/*
	The class Node represents the internal ruby node, a node is a piece of ruby code used
	for represent ruby methods in memory and other executable entities, many nodes come from
	the ruby source code and may be associated with a file and line where thats node are defined
	*/
	rb_cNode = rb_define_class("Node", rb_cObject);
	rb_define_method(rb_cNode, "line", rb_node_line, 0);
	rb_define_method(rb_cNode, "file", rb_node_file, 0);


	intern_owner = rb_intern("owner");
	intern_name = rb_intern("name");
	intern_sym = rb_intern("to_sym");
}
#else

void  Init_getsource_base() {
}

#endif

