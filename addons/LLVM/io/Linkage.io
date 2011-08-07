LLVM Linkage := Object clone do(
  ExternalLinkage := 0                  /**< Externally visible function */
  AvailableExternallyLinkage := 1
  LinkOnceAnyLinkage := 2               /**< Keep one copy of function when linking (inline)*/
  LinkOnceODRLinkage := 3               /**< Same, but only replaced by something equivalent. */
  WeakAnyLinkage := 4                   /**< Keep one copy of function when linking (weak) */
  WeakODRLinkage := 5                   /**< Same, but only replaced by something equivalent. */
  AppendingLinkage := 6                 /**< Special purpose, only applies to global arrays */
  InternalLinkage := 7                  /**< Rename collisions when linking (static functions) */
  PrivateLinkage := 8                   /**< Like Internal, but omit from symbol table */
  DLLImportLinkage := 9                 /**< Function to be imported from DLL */
  DLLExportLinkage := 10                /**< Function to be accessible from DLL */
  ExternalWeakLinkage := 11             /**< ExternalWeak linkage description */
  GhostLinkage := 12                    /**< Obsolete */
  CommonLinkage := 13                   /**< Tentative definitions */
  LinkerPrivateLinkage := 14            /**< Like Private, but linker removes. */
  LinkerPrivateWeakLinkage := 15        /**< Like LinkerPrivate, but is weak. */
  LinkerPrivateWeakDefAutoLinkage := 16 /**< Like LinkerPrivateWeak, but possibly hidden. */
)