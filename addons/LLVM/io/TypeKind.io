LLVM TypeKind := Object clone do(
  voidTypeKind        /**< type with no size */
  floatTypeKind       /**< 32 bit floating point type */
  doubleTypeKind      /**< 64 bit floating point type */
  x86_FP80TypeKind    /**< 80 bit floating point type (X87) */
  fp128TypeKind       /**< 128 bit floating point type (112-bit mantissa)*/
  ppc_FP128TypeKind   /**< 128 bit floating point type (two 64-bits) */
  labelTypeKind       /**< Labels */
  integerTypeKind     /**< Arbitrary bit width integers */
  functionTypeKind    /**< Functions */
  structTypeKind      /**< Structures */
  arrayTypeKind       /**< Arrays */
  pointerTypeKind     /**< Pointers */
  opaqueTypeKind      /**< Opaque: type with unknown structure */
  vectorTypeKind      /**< SIMD 'packed' format, or other vector type */
  metadataTypeKind    /**< Metadata */
)