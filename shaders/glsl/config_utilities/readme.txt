
 || NEWB SHADER SETTINGS
 || USAGE INSTRUCTIONS
  _________________________________
 |                                 |
 | Warning! :                      |
 | Making wrong changes to the     |
 | files may cause shader to fail  |
 |_________________________________|

 Make your changes and save the file
 Changes update automatically when you launch minecraft
 No need to restart the game completely to see changes :P

 Note: Some files have parts of code after
 configuration section. Don't mess with the
 code section unless you know coding

""""""""""""""""""""""""""""""""""""""""""""
 Toggle options

  • add "//" before "#define" to turn it OFF

  #define EXAMPLE   -> means ON
  //#define EXAMPLE -> means OFF
____________________________________________

 Value options

  • values must be in decimal format
  • values must not be negative 
  • don't toggle unless specified "Toggle + Value"

  #define example <your value here>
____________________________________________

 Color options

  • colors are in RGB format
  • value range 0.0 - 1.0

  const vec3 example = vec3(<red>,<green>,<blue>);

  Some color examples
    vec3(0.0,0.0,0.0) - black
    vec3(1.0,1.0,1.0) - white
    vec3(1.0,0.0,0.0) - red
    vec3(1.0,0.0,1.0) - magenta
____________________________________________

 Type options

  • 0,1,2,3... (choose between types using numbers)

  // <read this>
  #define EXAMPLE_TYPE 2
____________________________________________

 Toggle + Value options

  • Value option which can be be toggled to disable effect

  #define EXAMPLE 1.5
____________________________________________

 Toggle + Color options

  • Color option which can be be toggled to disable effect

  #define EXAMPLE vec3(<red>,<green>,<blue>)

"""""""""""""""""""""""""""""""""""""""""""""

 Send your suggestions to VeteranDev :P
 ( ･ω･)☞ - Discord - VeteranDev#2969
           Instagram - veteran.dev

