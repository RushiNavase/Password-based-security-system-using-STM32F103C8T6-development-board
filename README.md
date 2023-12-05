# Password-based-security-system-using-STM32F103C8T6-development-board
Hardware required:-STM32F103C8T6-development-board,4*4 keypad matrix,16*2 lcd dispaly,leds,buzzer,jumper Wires and Breadboard.
The System Design Flow:
 Initialization:
   - The `SystemClock_Config` function configures the system clock.
   - `MX_GPIO_Init` initializes the GPIO pins for input and output.
   - `lcd_init` initializes the LCD display.

 Keypad Reading:
   - The `key_Detect` function reads the state of the keypad.
   - The function 'key_Detect' makes the one after other row High and check the respective column to detect Key press
   - Functions `check_R1`, `check_R2`, `check_R3`, and `check_R4` check which key is pressed in each row.
   - The `key_Detect` function cycles through each row and column of the keypad matrix, returning the pressed key.

Password Checking and Actions:
   - The `checkcode` function checks if the entered password matches a predefined password (`arr2`).
   - The `pass_change` function checks if the entered password matches a predefined code (`arr3`) to trigger a password change.
   - `Hide_pass` function prints '*' on the LCD to hide the entered password.

 Main Loop
   - In the `main` function, the program enters an infinite loop (`while(1)`) and continuously calls `checkKeypad`.
   - `checkKeypad` repeatedly reads the keypad, handles password entry and checks for access or denial.
   - If the password is correct, it grants access, displays a success message, and blinks an LED.
   - If the password is incorrect, it denies access, displays a failure message, and activates a buzzer.
LCD Display:
   - The LCD is used to display messages and feedback to the user.

Delay Handling:
   - The `HAL_Delay` function is used to introduce delays in the program, ensuring proper functioning of the keypad and LCD interactions.

Password Change Workflow:
   - If the user chooses to change the password, the program guides them through the process, including entering the old password, verifying it, and entering a new password.

Feedback and Indicators:
    - LEDs and a buzzer are used to provide feedback to the user regarding successful or unsuccessful attempts.

Security Measures:
    - The system has basic security measures such as a buzzer for indicating incorrect attempts, a delay after successful entry, and a password change option.



