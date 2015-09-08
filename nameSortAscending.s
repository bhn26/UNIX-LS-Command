/*
 * Filename: nameSortAscending.s
 * Description: Sorts the name member field of given table struct array and
 *              the sorts it alphebetically.
 */

        .global nameSortAscending ! The symbol to be globally visible so
                                ! we can call this function from other modules.

        .section ".data"        ! The data segment begins here

        .section ".text"        ! The text segment begins here

/*
 * Function name: nameSortAscending()
 * Function prototype: int nameSortAscending( const void *p1, const void *p2 );
 * Description: Sorts the strings alphebetically.
 * Parameters:
 *      arg 1: const void *p1 -- the ptr that gets passed into this function
 *      arg 2: const void *p2 -- the ptr that gets passed into this function
 *
 * Side Effects: Returns an int value with ascending name order
 * Error Conditions: None
 * Return Value: Int
 *
 * Registers Used:
 *      %i0 - arg 1 -- the char passed in to this function
 *      %i1 - arg 2 -- the char passed in to this function
 *
 *      %o0 - param 1 to be used to compare with param 2
 *      %o1 - param 2 to be used to compare with param 1
 */

nameSortAscending:
        save    %sp, -96, %sp   ! Save caller's window; if different than -96
                                ! then comment on how that value was calculated.

        mov     %i0, %o0        ! Mov incoming params to regs
	mov     %i1, %o1      

        call    strcmp, 2       ! Call strcmp
	nop

	mov     %o0, %i0        ! Mov results to output reg

	ret                     ! Return from subroutine
	restore                 ! Restore caller's window; in "ret" delay slot
