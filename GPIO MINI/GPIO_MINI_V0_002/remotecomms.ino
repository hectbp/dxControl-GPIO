#include <Arduino.h>

/*
mini gpio v0.002
Copyright (C) Darren Siepka
A full copy of the license may be found in the projects root directory

Based on code by Josh Stewart for the Speeduino project , see www.Speeduino.com for more info
*/

/*
This is called when a command is received over seriallink from external source
It parses the command and calls the relevant function
*/
#include "remotecomms.h"
#include "globals.h"

void remote_serial_command()
{

    switch (SERIALLink.read())
          {
          case 'A':
                  while (SERIALLink.available() == 0) {}
                  replylength = (SERIALLink.read());              //read in reply length
                  for (byte rdata = 0; rdata < replylength; rdata++) //read x bytes of data according to replylength
                      {
                       realtimebuffer[rdata] = (SERIALLink.read());
                      }
          break;  

          case 'r':           
                byte cmd;
       if ( SERIALLink.available() >= 2)
      {
        cmd =  SERIALLink.read();                    

          if ((configPage1.num_bytes[(cmd-64)]&3) == 1) //(rlength == 1)
            {
              realtimebuffer[0] = SERIALLink.read();
              realtimebuffer[1] = 0;
            }
          if ((configPage1.num_bytes[(cmd-64)]&3) == 2) //(rlength == 2)
            {
              realtimebuffer[0] = SERIALLink.read();
              realtimebuffer[1] = SERIALLink.read();  
            }
            currentStatus.EXin[(cmd-64)] = word(realtimebuffer[1],realtimebuffer[0]) ;
      }                                        
          break;
        }

return;
 
}

void getExternalInput(uint8_t Xchan)
{
  uint16_t exOffset;
  uint16_t exLength;

  //now lookup speeduino output offset from list based on can address 
  //configPage1.speeduinoBaseCan holds the base address

  if (configPage1.INdata_from_Can[(Xchan-1)] == configPage1.speeduinoBaseCan)
      {
       switch ((configPage1.speeduinoConnection&3))   //the bitwise & blanks off the unused upper 6 bits
          {
          case 1:         //if direct connected to serial3?
          exOffset = configPage1.data_from_offset[(Xchan-1)];
          exLength = (configPage1.num_bytes[(Xchan-1)]&3);
          SERIALLink.write(commandletterr);          // send command letter to the Speeduino
          SERIALLink.write(tsCanId);                 // canid
          SERIALLink.write((64+(Xchan-1)));                    // cmd
          SERIALLink.write(lowByte(exOffset));
          SERIALLink.write(highByte(exOffset));
          SERIALLink.write(lowByte(exLength));
          SERIALLink.write(highByte(exLength));      
         break;

         case 2:
          // send via canbus   
         break;
          }
      }    
   else
      {
       //address is not speeduino so talk to the other device via canbus
       //make canbus calls 
      }

}      
