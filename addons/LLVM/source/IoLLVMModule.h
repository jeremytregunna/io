//metadoc LLVM copyright Jeremy Tregunna, 2011
//metadoc LLVM license MIT

#ifndef IOLLVMMODULE_DEFINED
#define IOLLVMMODULE_DEFINED 1

#include "IoObject.h"
#include "IoMessage.h"
#include <llvm-c/Core.h>

typedef IoObject IoLLVMModule;

typedef struct
{
	LLVMModuleRef module;
} IoLLVMModuleData;

IoLLVMModule* IoLLVMModule_proto(void*);
IoLLVMModule* IoLLVMModule_rawClone(IoLLVMModule*);
IoLLVMModule* IoLLVMModule_new(void*);
void IoLLVMModule_free(IoLLVMModule*);

/* Creates a module with a name, and optional context */
IoObject* IoLLVMModule_with(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_dataLayout(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_setDataLayout(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_target(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_setTarget(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_addTypeName(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_removeTypeName(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_getTypeByName(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_dump(IoObject*, IoObject*, IoMessage*);
IoObject* IoLLVMModule_setModuleInlineAsm(IoObject*, IoObject*, IoMessage*);

#endif
