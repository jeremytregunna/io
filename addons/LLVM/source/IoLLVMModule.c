//metadoc LLVM copyright Jeremy Tregunna, 2011
//metadoc LLVM license MIT
/*metadoc LLVM description
Binds the LLVM C bindings to Io.
*/

#include "IoState.h"
#include "IoLLVMModule.h"

#define DATA(self) ((IoLLVMModuleData*)IoObject_dataPointer(self))

IoTag* IoLLVMModule_newTag(void* state)
{
	IoTag* tag = IoTag_newWithName_("LLVMModule");

	IoTag_state_(tag, state);
	IoTag_freeFunc_(tag, (IoTagFreeFunc*)IoLLVMModule_free);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc*)IoLLVMModule_rawClone);

	return tag;
}

IoLLVMModule* IoLLVMModule_proto(void* state)
{
	IoObject* self = IoObject_new(state);
	IoObject_tag_(self, IoLLVMModule_newTag(state));

	IoObject_setDataPointer_(self, calloc(1, sizeof(IoLLVMModuleData)));
	IoState_registerProtoWithFunc_(state, self, IoLLVMModule_proto);
	
	{
		IoMethodTable methodTable[] = {
		{"with", IoLLVMModule_with},
		{"dataLayout", IoLLVMModule_dataLayout},
		{"setDataLayout", IoLLVMModule_setDataLayout},
		{"target", IoLLVMModule_target},
		{"setTarget", IoLLVMModule_setTarget},
		{"addTypeName", IoLLVMModule_addTypeName},
		{"deleteTypeName", IoLLVMModule_deleteTypeName},
		{"getTypeByName", IoLLVMModule_getTypeByName},
		{NULL, NULL},
		};
		
		IoObject_addMethodTable_(self, methodTable);
	}

    return self;
}

IoLLVMModule* IoLLVMModule_rawClone(IoLLVMModule* proto)
{
	IoLLVMModule* self = IoObject_rawClonePrimitive(proto);
    IoObject_setDataPointer_(self, cpalloc(DATA(proto), sizeof(IoLLVMModuleData)));
	return self;
}

/* ----------------------------------------------------------- */

IoLLVMModule* IoLLVMModule_new(void* state)
{
	IoObject* proto = IoState_protoWithInitFunction_(state, IoLLVMModule_proto);
	return IOCLONE(proto);
}

void IoLLVMModule_free(IoLLVMModule *self) 
{ 
	LLVMDisposeModule(DATA(self)->module);
	free(IoObject_dataPointer(self));
}

/* ----------------------------------------------------------- */

IO_METHOD(LLVMModule, with)
{ 
	IoSeq* name = IoMessage_locals_seqArgAt_(m, locals, 0);
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 1); // LLVMContextRef
	IoLLVMModule* r = IoLLVMModule_new(self->state);

	if(ISNIL(context))
		DATA(r)->module = LLVMModuleCreateWithName(CSTRING(name));
	else
		DATA(r)->module = LLVMModuleCreateWithNameInContext(CSTRING(name), IoLLVMContext_getContextRef(context));

	return r;
}

IO_METHOD(LLVMModule, dataLayout)
{
	return IOSTRING(LLVMGetDataLayout(DATA(self)->module));
}

IO_METHOD(LLVMModule, setDataLayout)
{
	IoSeq* seq = IoMessage_locals_seqArgAt_(m, locals, 0);
	LLVMSetDataLayout(DATA(self)->module, CSTRING(seq));
	return self;
}

IO_METHOD(LLVMModule, target)
{
	return IOSTRING(LLVMGetTarget(DATA(self)->module));
}

IO_METHOD(LLVMModule, setTarget)
{
	IoSeq* seq = IoMessage_locals_seqArgAt_(m, locals, 0);
	LLVMSetTarget(DATA(self)->module, CSTRING(seq));
	return self;
}

IO_METHOD(LLVMModule, addTypeName)
{
	IoSeq* name = IoMessage_locals_seqArgAt_(m, locals, 0);
	IoLLVMType* type = IoMessage_locals_valueArgAt_(m, locals, 1);

	LLVMBool ret = LLVMAddTypeName(DATA(self)->module, CSTRING(name), IoLLVMType_getTypeRef(type));

	return IOBOOL(self, ret);
}

IO_METHOD(LLVMModule, deleteTypeName)
{
	IoSeq* name = IoMessage_locals_seqArgAt_(m, locals, 0);
	LLVMDeleteTypeName(DATA(self)->module, CSTRING(name));
	return self;
}

IO_METHOD(LLVMModule, getTypeByName)
{
	IoSeq* name = IoMessage_locals_seqArgAt_(m, locals, 0);
	IoLLVMType* type = LLVMGetTypeByName(DATA(self)->module, CSTRING(name));
	return type;
}

IO_METHOD(LLVMModule, dump)
{
	LLVMDumpModule(DATA(self)->module);
	return self;
}

IO_METHOD(LLVMModule, setModuleInlineAsm)
{
	IoSeq* assembly = IoMessage_locals_seqArgAt_(m, locals, 0);
	LLVMSetModuleInlineAsm(DATA(self)->module, CSTRING(assembly));
	return self;
}
