LLVM Predicate := Object clone do(
  realPredicateFalse := 0 /**< Always false (always folded) */
  realOEQ := 1            /**< True if ordered and equal */
  realOGT := 2            /**< True if ordered and greater than */
  realOGE := 3            /**< True if ordered and greater than or equal */
  realOLT := 4            /**< True if ordered and less than */
  realOLE := 5            /**< True if ordered and less than or equal */
  realONE := 6            /**< True if ordered and operands are unequal */
  realORD := 7            /**< True if ordered (no nans) */
  realUNO := 8            /**< True if unordered: isnan(X) | isnan(Y) */
  realUEQ := 9            /**< True if unordered or equal */
  realUGT := 10           /**< True if unordered or greater than */
  realUGE := 11           /**< True if unordered, greater than, or equal */
  realULT := 12           /**< True if unordered or less than */
  realULE := 13           /**< True if unordered, less than, or equal */
  realUNE := 14           /**< True if unordered or not equal */
  realPredicateTrue := 15 /**< Always true (always folded) */
)