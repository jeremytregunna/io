//metadoc LLVM copyright Jeremy Tregunna, 2011
//metadoc LLVM license MIT
/*metadoc LLVM description
Binds the LLVM C bindings to Io.
*/

#include "IoState.h"
#include "IoLLVMTypes.h"

#define DATA(self) ((IoLLVMTypesData*)IoObject_dataPointer(self))

IoTag* IoLLVMTypes_newTag(void* state)
{
	IoTag* tag = IoTag_newWithName_("LLVMTypes");

	IoTag_state_(tag, state);
	IoTag_freeFunc_(tag, (IoTagFreeFunc*)IoLLVMTypes_free);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc*)IoLLVMTypes_rawClone);

	return tag;
}

IoLLVMTypes* IoLLVMTypes_proto(void* state)
{
	IoObject* self = IoObject_new(state);
	IoObject_tag_(self, IoLLVMTypes_newTag(state));

	IoObject_setDataPointer_(self, calloc(1, sizeof(IoLLVMTypesData)));
	IoState_registerProtoWithFunc_(state, self, IoLLVMTypes_proto);
	
	{
		IoMethodTable methodTable[] = {
		{"getTypeKind", IoLLVMTypes_getTypeKind},
		{"getContext", IoLLVMTypes_getContext},
		{"bool", IoLLVMTypes_boolType},
		{"int8", IoLLVMTypes_int8},
		{"int16", IoLLVMTypes_int16},
		{"int32", IoLLVMTypes_int32},
		{"bigint", IoLLVMTypes_bigint},
		{"width", IoLLVMTypes_width},
		{"float", IoLLVMTypes_floatType},
		{"double", IoLLVMTypes_doubleType},
		{"x86fp80", IoLLVMTypes_x86fp80},
		{"fp128", IoLLVMTypes_fp128},
		{"ppcfp128", IoLLVMTypes_ppcfp128},
		{"function", IoLLVMTypes_function},
		{"isFunctionVarArg", IoLLVMTypes_isFunctionVarArg},
		{"getReturnType", IoLLVMTypes_getReturnType},
		{"countParamTypes", IoLLVMTypes_countParamTypes},
		{"getParamTypes", IoLLVMTypes_getParamTypes},
		{"struct", IoLLVMTypes_structType},
		{"countStructElementTypes", IoLLVMTypes_countStructElementTypes},
		{"getStructElementTypes", IoLLVMTypes_getStructElementTypes},
		{"isPackedStruct", IoLLVMTypes_isPackedStruct},
		{"array", IoLLVMTypes_array},
		{"pointer", IoLLVMTypes_pointer},
		{"vector", IoLLVMTypes_vector},
		{"getElementType", IoLLVMTypes_getElementType},
		{"getArrayLength", IoLLVMTypes_getArrayLength},
		{"getPointerAddressSpace", IoLLVMTypes_getPointerAddressSpace},
		{"getVectorSize", IoLLVMTypes_getVectorSize},
		{"void", IoLLVMTypes_voidType},
		{"label", IoLLVMTypes_label},
		{"opaque", IoLLVMTypes_opaque},
		{NULL, NULL},
		};
		
		IoObject_addMethodTable_(self, methodTable);
	}

    return self;
}

IoLLVMTypes* IoLLVMTypes_rawClone(IoLLVMTypes* proto)
{
	IoLLVMTypes* self = IoObject_rawClonePrimitive(proto);
    IoObject_setDataPointer_(self, cpalloc(DATA(proto), sizeof(IoLLVMTypesData)));
	return self;
}

/* ----------------------------------------------------------- */

IoLLVMTypes* IoLLVMTypes_new(void* state)
{
	IoObject* proto = IoState_protoWithInitFunction_(state, IoLLVMTypes_proto);
	return IOCLONE(proto);
}

void IoLLVMTypes_free(IoLLVMTypes *self) 
{ 
	LLVMTypesDispose(DATA(self)->context);
	free(IoObject_dataPointer(self));
}

/* ----------------------------------------------------------- */

IO_METHOD(LLVMTypes, getTypeKind)
{ 
	return IONUMBER(LLVMGetTypeKind(DATA(self)->type));
}

IO_METHOD(LLVMTypes, getContext)
{
	IoLLVMContext* context = IoLLVMContext_new(self->state);
	DATA(context)->context = LLVMGetTypeContext(DATA(self)->type);
	return context;
}

static inline IoLLVMTypes* IoLLVMTypes_context_(IoLLVMContext* context, LLVMTypeRef (*withContextFunc)(LLVMContextRef C), LLVMTypeRef(*withoutContextFunc)(void))
{
	IoLLVMTypes* r = IoLLVMTypes_new(context->state);

	if(context)
		DATA(r)->type = withContextFunc(DATA(context)->context);
	else
		DATA(r)->type = withoutContextFunc();

	return r;
}

IO_METHOD(LLVMTypes, boolType)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMInt1TypeInContext, LLVMInt1Type);
}

IO_METHOD(LLVMTypes, int8)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMInt8TypeInContext, LLVMInt8Type);
}

IO_METHOD(LLVMTypes, int16)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMInt16TypeInContext, LLVMInt16Type);
}

IO_METHOD(LLVMTypes, int32)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMInt32TypeInContext, LLVMInt32Type);
}

IO_METHOD(LLVMTypes, bigint)
{
	IoNumber* width = IoMessage_locals_numberArgAt_(m, locals, 0);
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 1);
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);

	if(context)
		DATA(r)->type = LLVMIntTypeInContext(context, CNUMBER(width));
	else
		DATA(r)->type = LLVMIntType(CNUMBER(width));

	return r;
}

IO_METHOD(LLVMTypes, width)
{
	return IONUMBER(LLVMGetIntTypeWidth(DATA(self)->type));
}

IO_METHOD(LLVMTypes, floatType)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMFloatTypeInContext, LLVMFloatType);
}

IO_METHOD(LLVMTypes, doubleType)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMDoubleTypeInContext, LLVMDoubleType);
}

IO_METHOD(LLVMTypes, x86fp80)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMX86FP80TypeInContext, LLVMX86FP80Type);
}

IO_METHOD(LLVMTypes, fp128)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMFP128TypeInContext, LLVMFP128Type);
}

IO_METHOD(LLVMTypes, ppcfp128)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMPPCFP128TypeInContext, LLVMPPCFP128Type);
}

IO_METHOD(LLVMTypes, function)
{
	IoLLVMTypes* returnType = IoMessage_locals_valueArgAt_(m, locals, 0);
	IoList* paramTypes = IoMessage_locals_listArgAt_(m, locals, 1);
	int isVarArg = IoMessage_locals_boolArgAt_(m, locals, 2);
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	List* params = IoList_rawList(paramTypes);

	DATA(r)->type = LLVMFunctionType(DATA(returnType)->type, params->items, params->size, isVarArg);

	return r;
}

IO_METHOD(LLVMTypes, isFunctionVarArg)
{
	return IOBOOL(LLVMIsFunctionVarArg(DATA(self)->type));
}

IO_METHOD(LLVMTypes, getReturnType)
{
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	DATA(r)->type = LLVMGetReturnType(DATA(self)->type);
	return r;
}

IO_METHOD(LLVMTypes, countParamTypes)
{
	return IONUMBER(LLVMCountParamTypes(DATA(self)->type));
}

IO_METHOD(LLVMTypes, getParamTypes)
{
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	LLVMTypeRef dest = NULL;
	LLVMGetParamTypes(DATA(self)->type, &dest);
	DATA(r)->type = dest;
	return r;
}

IO_METHOD(LLVMTypes, structType)
{
	IoList* elementTypes = IoMessage_locals_listArgAt_(m, locals, 0);
	int isPacked = IoMessage_locals_boolArgAt_(m, locals, 1);
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 2);
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	List* raw = IoList_rawList(elementTypes);

	if(context)
		DATA(r)->type = LLVMStructTypeInContext(context, raw->items, raw->size, isPacked);
	else
		DATA(r)->type = LLVMStructType(raw->items, raw->size, isPacked);

	return r;
}

IO_METHOD(LLVMTypes, countStructElementTypes)
{
	return IONUMBER(LLVMCountStructElementTypes(DATA(self)->type));
}

IO_METHOD(LLVMTypes, getStructElementTypes)
{
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	LLVMTypeRef dest = NULL;
	LLVMGetStructElementTypes(DATA(self)->type, &dest);
	DATA(r)->type = dest;
	return r;
}

IO_METHOD(LLVMTypes, isPackedStruct)
{
	return IOBOOL(LLVMIsPackedStruct(DATA(self)->type));
}

IO_METHOD(LLVMTypes, array)
{
	IoNumber* count = IoMessage_locals_numberArgAt_(m, locals, 0);
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	DATA(r)->type = LLVMArrayType(DATA(self)->type, CNUMBER(count));
	return r;
}

IO_METHOD(LLVMTypes, pointer)
{
	IoNumber* addressSpace = IoMessage_locals_numberArgAt_(m, locals, 0);
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	DATA(r)->type = LLVMPointerType(DATA(self)->type, CNUMBER(addressSpace));
	return r;
}

IO_METHOD(LLVMTypes, vector)
{
	IoNumber* count = IoMessage_locals_numberArgAt_(m, locals, 0);
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	DATA(r)->type = LLVMArrayType(DATA(self)->type, CNUMBER(count));
	return r;
}

IO_METHOD(LLVMTypes, getElementType)
{
	IoLLVMTypes* r = IoLLVMTypes_new(self->state);
	DATA(r)->type = LLVMGetElementType(DATA(self)->type);
	return r;
}

IO_METHOD(LLVMTypes, getArrayLength)
{
	return IONUMBER(LLVMGetArrayLength(DATA(self)->type));
}

IO_METHOD(LLVMTypes, getPointerAddressSpace)
{
	return IONUMBER(LLVMGetPointerAddressSpace(DATA(self)->type));
}

IO_METHOD(LLVMTypes, getVectorSize)
{
	return IONUMBER(LLVMGetVectorSize(DATA(self)->type));
}

IO_METHOD(LLVMTypes, voidType)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMVoidTypeInContext, LLVMVoidType);
}

IO_METHOD(LLVMTypes, label)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMVoidTypeInContext, LLVMVoidType);
}

IO_METHOD(LLVMTypes, opaque)
{
	IoLLVMContext* context = IoMessage_locals_valueArgAt_(m, locals, 0);
	return IoLLVMTypes_context_(context, LLVMVoidTypeInContext, LLVMVoidType);
}
