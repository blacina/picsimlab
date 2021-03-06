/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2019-2020  Luis Claudio Gambôa Lopes

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   For e-mail suggestions :  lcgamboa@yahoo.com
   ######################################################################## */

#include"../picsimlab1.h"
#include"../picsimlab4.h"
#include"../picsimlab5.h"
#include"part_MI2C_24CXXX.h"

/* outputs */
enum
{
 O_P1, O_P2, O_P3, O_P4, O_P5, O_P6, O_P7, O_P8, O_IC
};

const char pin_names[8][10] = {"A0", "A1", "A2", "VSS", "SDA", "SCL", "WP", "VCC"};
const char pin_values[8][10] = {
 {0},
 {1},
 {2},
 "GND",
 {3},
 {4},
 "GND",
 "+5V"
};

cpart_MI2C_24CXXX::cpart_MI2C_24CXXX(unsigned x, unsigned y)
{
 X = x;
 Y = y;
 ReadMaps ();
 Bitmap = NULL;

 lxImage image;

 image.LoadFile (Window1.GetSharePath () + lxT ("parts/") + GetPictureFileName ());


 Bitmap = new lxBitmap (image, &Window5);
 image.Destroy ();
 canvas.Create (Window5.GetWWidget (), Bitmap);

 kbits = 4;

 mi2c_init (&mi2c, kbits);
 mi2c_rst (&mi2c);

 input_pins[0] = 0;
 input_pins[1] = 0;
 input_pins[2] = 0;
 input_pins[3] = 0;
 input_pins[4] = 0;
};

cpart_MI2C_24CXXX::~cpart_MI2C_24CXXX(void)
{
 mi2c_end (&mi2c);
 delete Bitmap;
 canvas.Destroy ();
}

void
cpart_MI2C_24CXXX::Draw(void)
{

 int i;

 canvas.Init ();

 lxFont font (8, lxFONTFAMILY_TELETYPE, lxFONTSTYLE_NORMAL, lxFONTWEIGHT_BOLD);
 canvas.SetFont (font);

 for (i = 0; i < outputc; i++)
  {

   switch (output[i].id)
    {
    case O_IC:
     char buff[10];
     snprintf(buff,9,"24C%02i",kbits);
     canvas.SetColor (0, 0, 0);
     canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);
     canvas.SetFgColor (255, 255, 255);
     canvas.Text (buff, output[i].x1, output[i].y2 - 15);
     break;
    default:
     canvas.SetColor (49, 61, 99);
     canvas.Rectangle (1, output[i].x1, output[i].y1, output[i].x2 - output[i].x1, output[i].y2 - output[i].y1);

     canvas.SetFgColor (255, 255, 255);
     canvas.RotatedText (pin_names[output[i].id - O_P1], output[i].x1, output[i].y2, 90.0);

     int pinv = pin_values[output[i].id - O_P1][0];
     if (pinv > 10)
      {
       canvas.SetFgColor (155, 155, 155);
       canvas.RotatedText (pin_values[output[i].id - O_P1], output[i].x1, output[i].y2 - 30, 90.0);
      }
     else
      {
       if (input_pins[pinv] == 0)
        canvas.RotatedText ("NC", output[i].x1, output[i].y2 - 30, 90.0);
       else
        canvas.RotatedText (Window5.GetPinName (input_pins[pinv]), output[i].x1, output[i].y2 - 30, 90.0);
      }
     break;
    }


  }

 canvas.End ();

}

unsigned short
cpart_MI2C_24CXXX::get_in_id(char * name)
{
 printf ("Erro input '%s' don't have a valid id! \n", name);
 return -1;
};

unsigned short
cpart_MI2C_24CXXX::get_out_id(char * name)
{

 if (strcmp (name, "P1") == 0)return O_P1;
 if (strcmp (name, "P2") == 0)return O_P2;
 if (strcmp (name, "P3") == 0)return O_P3;
 if (strcmp (name, "P4") == 0)return O_P4;
 if (strcmp (name, "P5") == 0)return O_P5;
 if (strcmp (name, "P6") == 0)return O_P6;
 if (strcmp (name, "P7") == 0)return O_P7;
 if (strcmp (name, "P8") == 0)return O_P8;

 if (strcmp (name, "IC") == 0)return O_IC;

 printf ("Erro output '%s' don't have a valid id! \n", name);
 return 1;
};

String
cpart_MI2C_24CXXX::WritePreferences(void)
{
 char prefs[256];

 sprintf (prefs, "%hhu,%hhu,%hhu,%hhu,%hhu,%u", input_pins[0], input_pins[1], input_pins[2], input_pins[3], input_pins[4], kbits);

 return prefs;
}

void
cpart_MI2C_24CXXX::ReadPreferences(String value)
{
 sscanf (value.c_str (), "%hhu,%hhu,%hhu,%hhu,%hhu,%u", &input_pins[0], &input_pins[1], &input_pins[2], &input_pins[3], &input_pins[4], &kbits);

 mi2c_end (&mi2c);
 mi2c_init (&mi2c, kbits);
 mi2c_rst (&mi2c);

 Reset ();
}

CPWindow * WProp_MI2C_24CXXX;

void
cpart_MI2C_24CXXX::ConfigurePropertiesWindow(CPWindow * wprop)
{
 String Items = Window5.GetPinsNames ();
 String spin;
 WProp_MI2C_24CXXX = wprop;

 ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo1"))->SetItems (Items);
 if (input_pins[0] == 0)
  ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo1"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[0]);
   ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo1"))->SetText (itoa (input_pins[0]) + "  " + spin);
  }

 ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo2"))->SetItems (Items);
 if (input_pins[1] == 0)
  ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo2"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[1]);
   ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo2"))->SetText (itoa (input_pins[1]) + "  " + spin);
  }

 ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo3"))->SetItems (Items);
 if (input_pins[2] == 0)
  ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo3"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[2]);
   ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo3"))->SetText (itoa (input_pins[2]) + "  " + spin);
  }


 ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo5"))->SetItems (Items);
 if (input_pins[3] == 0)
  ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo5"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[3]);
   ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo5"))->SetText (itoa (input_pins[3]) + "  " + spin);
  }

 ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo6"))->SetItems (Items);
 if (input_pins[4] == 0)
  ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo6"))->SetText ("0  NC");
 else
  {
   spin = Window5.GetPinName (input_pins[4]);
   ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo6"))->SetText (itoa (input_pins[4]) + "  " + spin);
  }

 ((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo9"))->SetText (itoa (kbits));


 ((CButton*) WProp_MI2C_24CXXX->GetChildByName ("button1"))->EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CPWindow5::PropButtonRelease;
 ((CButton*) WProp_MI2C_24CXXX->GetChildByName ("button1"))->SetTag (1);

 ((CButton*) WProp_MI2C_24CXXX->GetChildByName ("button2"))->EvMouseButtonRelease = EVMOUSEBUTTONRELEASE & CPWindow5::PropButtonRelease;
}

void
cpart_MI2C_24CXXX::ReadPropertiesWindow(void)
{
 input_pins[0] = atoi (((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo1"))->GetText ());
 input_pins[1] = atoi (((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo2"))->GetText ());
 input_pins[2] = atoi (((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo3"))->GetText ());
 input_pins[3] = atoi (((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo5"))->GetText ());
 input_pins[4] = atoi (((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo6"))->GetText ());

 int nkbits = atoi (((CCombo*) WProp_MI2C_24CXXX->GetChildByName ("combo9"))->GetText ());

 if (nkbits != kbits)
  {
   kbits = nkbits;
   mi2c_end (&mi2c);
   mi2c_init (&mi2c, kbits);
   mi2c_rst (&mi2c);
  }
}

void
cpart_MI2C_24CXXX::Process(void)
{
 const picpin * ppins = Window5.GetPinsValues ();

 if ((input_pins[3] > 0)&&(input_pins[4] > 0))
  Window5.Set_i2c_bus (input_pins[3] - 1, mi2c_io (&mi2c, ppins[input_pins[4] - 1].value, ppins[input_pins[3] - 1].value));

 if (input_pins[3] > 0)
  Window5.SetPin (input_pins[3], Window5.Get_i2c_bus (input_pins[3] - 1));

}
