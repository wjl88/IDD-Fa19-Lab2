# Digital Timer
 
Include your responses to the bold questions below. Include snippets of code that explain what you did. Deliverables are due next Tuesday. Post your lab reports as README.md pages on your GitHub, and post a link to that on your main class hub page.

## Part A. Solder your LCD panel

**Take a picture of your soldered panel and add it here!**

>> picture taken (2)

## Part B. Writing to the LCD
 
**a. What voltage level do you need to power your display?**

3 V to power the display itself

**b. What voltage level do you need to power the display backlight?**

5 V to power the display backlight
   
**c. What was one mistake you made when wiring up the display? How did you fix it?**

I wired it upside down

**d. What line of code do you need to change to make it flash your name instead of "Hello World"?**
```
lcd.setCursor(0, 0);
lcd.print("William J Leon");
```
 
**e. Include a copy of your Lowly Multimeter code in your lab write-up.**

```
void debug( long i, int r ) {
  lcd.setCursor(0, r);
  lcd.print(i);
}

void f_readVolts() {
  int val = analogRead(A0);
  lcd.clear();
  debug(val,1);
  delay(300);
}
```


## Part C. Using a time-based digital sensor

**Upload a video of your working rotary encoder here.**


## Part D. Make your Arduino sing!

**a. How would you change the code to make the song play twice as fast?**
 
**b. What song is playing?**


## Part E. Make your own timer

**a. Make a short video showing how your timer works, and what happens when time is up!**

**b. Post a link to the completed lab report your class hub GitHub repo.**
