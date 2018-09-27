.data 

original_list: .space 100    # .space Reserves the next specified number of bytes in Data segment
sorted_list: .space 100

str0: .asciiz "Enter size of list (between 1 and 25): "
str1: .asciiz "Enter one list element: \n"
str2: .asciiz "Content of original list: "
str3: .asciiz "Enter a key to search for: "
str4: .asciiz "Content of sorted list: "
strYes: .asciiz "Key found!"
strNo: .asciiz "Key not found!"

newline: .asciiz "\n"
space: .asciiz " "

.text 

#This is the main program.
#It first asks user to enter the size of a list.
#It then asks user to input the elements of the list, one at a time.
#It then calls printList to print out content of the list.
#It then calls inSort to perform insertion sort
#It then asks user to enter a search key and calls bSearch on the sorted list.
#It then prints out search result based on return value of bSearch
main: 
	addi $sp, $sp -8
	sw $ra, 0($sp)
	li $v0, 4 
	la $a0, str0 
	syscall 
	li $v0, 5	#read size of list from user
	syscall
	move $s0, $v0
	move $t0, $0
	la $s1, original_list
loop_in:
	li $v0, 4 
	la $a0, str1 
	syscall 
	sll $t1, $t0, 2
	add $t1, $t1, $s1
	li $v0, 5	#read elements from user
	syscall
	sw $v0, 0($t1)
	addi $t0, $t0, 1
	bne $t0, $s0, loop_in
	move $a0, $s1       # elements
	move $a1, $s0     #sizeoflist
	
	jal inSort	#Call inSort to perform insertion sort in original list
	
	sw $v0, 4($sp)
	li $v0, 4 
	la $a0, str2 
	syscall 
	la $a0, original_list
	move $a1, $s0
	jal printList	#Print original list
	li $v0, 4 
	la $a0, str4 
	syscall 
	lw $a0, 4($sp)
	jal printList	#Print sorted list
	
	li $v0, 4 
	la $a0, str3 
	syscall 
	li $v0, 5	#read search key from user
	syscall
	move $a3, $v0
	lw $a0, 4($sp)
	jal bSearch	#call bSearch to perform binary search
	
	beq $v0, $0, notFound
	li $v0, 4 
	la $a0, strYes 
	syscall 
	j end
	
notFound:
	li $v0, 4 
	la $a0, strNo 
	syscall 
end:
	lw $ra, 0($sp)
	addi $sp, $sp 8
	li $v0, 10 
	syscall
	
	
#printList takes in a list and its size as arguments. 
#It prints all the elements in one line.
printList:
	#Your implementation of printList here
        addi $sp, $sp, -4
	sw $a0, 0($sp)
	
	move $t0, $a0    #elements
	move $t1, $a1    #size
	li $t2, 0
print:	
	beq $t2, $t1, done
    	li $v0, 1
    	lw $a0, 0($t0)
    	syscall
    	
    	li $v0, 4
	la $a0, space
	syscall
	
    	addi $t0, $t0, 4
    	addi, $t2, $t2, 1
    	j print
      
done:          
        li $v0, 4
        la $a0, newline
	    syscall
	
        lw $a0, 0($sp)
        addi $sp, $sp, 4
	
        jr $ra
	
	
	
#inSort takes in a list and it size as arguments. 
#It performs INSERTION sort in ascending order and returns a new sorted list
#You may use the pre-defined sorted_list to store the result
inSort:   
    addi $sp, $sp, -8
    sw $ra, 0($sp)
    sw $s0, 4($sp)  
    sw $s1, 8($sp)   #store the orig array to stack pointer

    move $s0, $s1 # address of original array
    move $s1, $a1 # size of array
    addi $s2, $zero, 1 # sets i = 1

   
copyarray:
    la $t0, original_list
    la $t1, sorted_list
    addi $t6, $t6, 0 # iterator

copy:
    beq $s1, $t6, donecopy      #branch if iterator is equal to the size of the array
    lw $t2, ($t0)
    sw $t2, ($t1)               #copying the values to sorted_list
   
    addi $t0, $t0, 4            
    addi $t1, $t1, 4
    addi $t6, $t6, 1
    j copy

donecopy:
    la $t1, sorted_list
    move $s0, $t1           #s0 has the copy of the array

   

   #""""""""""""""""""""""""""""""""""""""""""""""""#

sort:
    move $t0, $s0   # get the base address from the new copy 
    move $t1, $a1   #size of array
    li $t2, 1      #loop counter starting from index 1

Loop:
    move $t0, $s0                #load array to $t0
    beq $t2, $t1, sortEnd   # sort ends while loop counter = size of array
    move $t3, $t2               #$t3 = index

swap:
    move $t0, $s0      #array base to $t0
    sll $t4, $t3, 2    #$t3 * 4, store into $t4
    add $t0, $t0, $t4  #base + (index * 4)
    beq $t3, 0, inc_counter   #while index > 0
    lw $t5, 0($t0)     #load array[index] to $t5
    lw $t6, -4($t0)    #load array[index-1] to $t6
    		       #swapping
    ble $t6, $t5, inc_counter
    lw $t7, 0($t0)
    sw $t6, 0($t0)
    sw $t7, -4($t0)
    addi $t3, $t3, -1
    j swap

inc_counter:
	addi $t2, $t2, 1   #increment counter by 1
	j Loop

sortEnd:
     lw $ra, 0($sp)
     lw $s0, 4($sp)      
     lw $s1, 8($sp)    # load the orig array from the stack pointer
     addi $sp, $sp, 8
    
     la $v0, sorted_list    # v0 has the base of the sorted list
	
     jr $ra
	
#bSearch takes in a list, its size, and a search key as arguments.
#It performs binary search RECURSIVELY to look for the search key.
#It will return a 1 if the key is found, or a 0 otherwise.
#Note: you MUST NOT use iterative approach in this function.
bSearch:
	#Your implementation of bSearch here
      addi $sp, $sp, -16
      sw $ra, 0($sp)
      sw $a0, 4($sp)   #base array
      sw $a1, 8($sp)   #size 
      sw $a3, 12($sp)  #search value
 
      
      srl $s0, $a1, 1   # cut the size into half
      sll $s1, $s0, 2   
      add $s1, $a0, $s1   # address of the middle index
      
      lw $t4, 0($s1)     #value in the middle
      
      
      beq $t4, $a3, valuefound
      beq $t4, $zero, valuenotfound
      bgt $t4, $a3, searchLeft 
      
      #search right
      add $a0, $s1, 4
      sub $a1, $a1, $s0
      
      jal bSearch
    
      j searchend
searchLeft:
          add $a1, $zero, $s0
          
          jal bSearch
          
          j searchend
          
valuefound:  
           li $v0, 1
           jr $ra
valuenotfound:
           li $v0, 0
           jr $ra
      
searchend:      
      lw $a3, 12($sp)
      lw $a1, 8($sp)
      lw $a0, 4($sp)  
      lw $ra, 0($sp)
      addi $sp, $sp, 16
      
      jr $ra
	
