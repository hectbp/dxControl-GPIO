void driveDisplay()
{
/* put your display code in here
    it is called at 10hz
    configure the data you want to see in TS
    then read the data directly from the variables
    currentStatus.EXin[0] to currentStatus.EXin[15] 
*/  
#if defined DISP1_ACTIVE 
     if (DISP1_I2C_ROUTE !=0){u8g2_1.setI2CAddress((DISP1_I2C_ROUTE*2));}
      u8g2_1.setFont(u8g2_font_ncenB14_tr);
      u8g2_1.firstPage();
      do {
          u8g2_1.setCursor(0, 20);
          u8g2_1.print(F("RPM "));
          u8g2_1.setCursor(50, 20);
          u8g2_1.print(currentStatus.EXin[0]);
          u8g2_1.setCursor(0, 50);
          u8g2_1.print(F("MAP "));
          u8g2_1.setCursor(50, 50);
          u8g2_1.print(currentStatus.EXin[1]);
          } while ( u8g2_1.nextPage() );
#endif

#if defined DISP2_ACTIVE  
    if (DISP2_I2C_ROUTE !=0){u8g2_2.setI2CAddress((DISP2_I2C_ROUTE*2));}
      u8g2_2.firstPage();
      do {
          u8g2_2.setFont(u8g2_font_logisoso58_tr);
          u8g2_2.drawStr(0,63,"1");
          } while ( u8g2_2.nextPage() );
#endif
}

void initialise_display()
{
#if defined DISP1_ACTIVE 
    u8g2_1.begin();
#endif    
#if defined DISP2_ACTIVE
    u8g2_2.begin();
#endif
} 
