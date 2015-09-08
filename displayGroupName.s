/*
 * Filename: displayGroupName.s
 * Description: This displays the group name of the file if the -l flag is
 *              requested upon user input. Takes in the st_gid field of the 
 *              file struct.
 */

        .global displayGroupName! Declares the symbol to be globally visible so
                                ! we can call this function from other modules.

        .section ".data"        ! The data segment begins here

displayS:
        .asciz "%-8s "

displayU:
        .asciz "%-8u "

        .section ".text"        ! The text segment begins here

/*
 * Function name: displayGroupName()
 * Function prototype: void displayGroupName( const gid_t gid );
 * Description: Takes in the file's gid member field which will be analyed
 *              and prints the group id of the current file.
 * Parameters: const gid_t gid is the member field of the current file that
 *             holds the gid.
 *      arg 1: const gid_t gid -- group id of passed gid_t
 *
 * Side Effects: Outputs the group name of the file
 * Error Conditions: None
 * Return Value: None
 *
 * Registers Used:
 *      %i0 - arg 1 -- the char passed in to this function
 *      %i1 - arg 2 -- the char passed in to this function
 *
 *      %l0 - param 1 to be used to compare with param 2
 *      %l1 - param 2 to be used to compare with param 1
 */

displayGroupName:
        save    %sp, -96, %sp   ! Save caller's window
                                ! then comment on how that value was calculated.

        set     groupOff, %l0   ! Sets and loads the offset
	ld      [%l0], %l0

        mov     %i0, %o0        ! Moved param into reg

	call    getgrgid        ! Calls getgrgid
	nop

	mov     %o0, %l1        ! Moves output to reg
        
	cmp     %l1, %g0        ! Cmps for null
	be      displayOther    ! Branch if true
	nop

        set     displayS, %o0   ! Sets the display format
        ld      [%l1+%l0], %o1  ! Loads the group name
	call    printf, 2       ! Prints it
	nop

	ret                     ! Return from subroutine
	restore                 ! Restore caller's window; in "ret" delay slot

displayOther:
        set     displayU, %o0   ! Sets the display format
	mov     %i0, %o1        ! Movs param to reg

	call    printf          ! Prints it
	nop

	ret                     ! Return from subroutine
	restore                 ! Restore caller's window; in "ret" delay slot
