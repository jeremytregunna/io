//metadoc LLVM copyright Jeremy Tregunna, 2011
//metadoc LLVM license MIT
/*metadoc LLVM description
Binds the LLVM C bindings to Io.
*/

#include "IoState.h"
#include "IoLLVMContext.h"

#define DATA(self) ((IoLLVMContextData*)IoObject_dataPointer(self))

IoTag* IoLLVMContext_newTag(void* state)
{
	IoTag* tag = IoTag_newWithName_("LLVMContext");

	IoTag_state_(tag, state);
	IoTag_freeFunc_(tag, (IoTagFreeFunc*)IoLLVMContext_free);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc*)IoLLVMContext_rawClone);

	return tag;
}

IoLLVMContext* IoLLVMContext_proto(void* state)
{
	IoObject* self = IoObject_new(state);
	IoObject_tag_(self, IoLLVMContext_newTag(state));

	IoObject_setDataPointer_(self, calloc(1, sizeof(IoLLVMContextData)));
	IoState_registerProtoWithFunc_(state, self, IoLLVMContext_proto);
	
	{
		IoMethodTable methodTable[] = {
		{"getGlobalContext", IoLLVMContext_getGlobalContext},
		{"getMDKindIDInContext", IoLLVMContext_getMDKindIDInContext}
		{NULL, NULL},
		};
		
		IoObject_addMethodTable_(self, methodTable);
	}

	DATA(self)->context = LLVMContextCreate();

    return self;
}

IoLLVMContext* IoLLVMContext_rawClone(IoLLVMContext* proto)
{
	IoLLVMContext* self = IoObject_rawClonePrimitive(proto);
    IoObject_setDataPointer_(self, cpalloc(DATA(proto), sizeof(IoLLVMContextData)));
	return self;
}

/* ----------------------------------------------------------- */

IoLLVMContext* IoLLVMContext_new(void* state)
{
	IoObject* proto = IoState_protoWithInitFunction_(state, IoLLVMContext_proto);
	return IOCLONE(proto);
}

void IoLLVMContext_free(IoLLVMContext *self) 
{ 
	LLVMContextDispose(DATA(self)->context);
	free(IoObject_dataPointer(self));
}

/* ----------------------------------------------------------- */

IO_METHOD(LLVMContext, getGlobalContext)
{ 
	IoLLVMContext* r = IoLLVMContext_new(self->state);
	DATA(r)->context = LLVMGetGlobalContext();
	return r;
}

IO_METHOD(LLVMContext, getMDKindIDInContext)
{
	IoSeq* name = IoMessage_locals_seqArgAt_(m, locals, 0);
	IoNumber* slen = IoMessage_locals_numberArgAt_(m, locals, 1);

	return IONUMBER(LLVMGetMDKindIDInContext(DATA(self)->context, CSTRING(name), CNUMBER(slen)));
}
