//metadoc LLVM copyright Jeremy Tregunna, 2011
//metadoc LLVM license MIT

#ifndef IOLLVMTYPES_DEFINED
#define IOLLVMTYPES_DEFINED 1

#include "IoObject.h"
#include "IoMessage.h"
#include <llvm-c/Core.h>

typedef IoObject IoLLVMTypes;

typedef struct
{
	LLVMTypeRef type;
} IoLLVMTypesData;

IoLLVMTypes* IoLLVMTypes_proto(void*);
IoLLVMTypes* IoLLVMTypes_rawClone(IoLLVMTypes*);
IoLLVMTypes* IoLLVMTypes_new(void*);
void IoLLVMTypes_free(IoLLVMTypes*);

IoObject* IoLLVMTypes_getTypeKind(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_getContext(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_boolType(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_int8(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_int16(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_int32(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_int64(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_bigint(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_width(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_float(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_double(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_x86fp80(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_fp128(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_ppcfp128(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_function(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_isFunctionVarArg(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_getReturnType(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_countParamTypes(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_getParamTypes(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_structType(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_countStructElementTypes(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_getStructElementTypes(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_isPackedStruct(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_array(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_pointer(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_vector(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_getElementType(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_getArrayLength(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_getPointerAddressSpace(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_getVectorSize(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_voidType(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_label(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMTypes_opaque(IoObject*, IoObject*, IoMessage*);

#endif
