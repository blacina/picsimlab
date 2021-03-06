/* ########################################################################

   PICsimLab - PIC laboratory simulator

   ########################################################################

   Copyright (c) : 2010-2020  Luis Claudio Gambôa Lopes

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

#ifndef CPWINDOW5 
#define CPWINDOW5

#include<lxrad.h>
#include"parts/part.h"
#include"parts/parts_defs.h"

#define IOINIT 70

class CPWindow5:public CPWindow
{
  public:
//lxrad automatic generated block start, don't edit below!
  /*#Controls*/
  CMenu menu1;
  CDraw draw1;
  CPMenu menu1_File;
  CPMenu menu1_Add;
  CPMenu pmenu2;
  CItemMenu pmenu2_Properties;
  CTimer timer1;
  CItemMenu menu1_File_Newconfiguration;
  CItemMenu menu1_File_Saveconfiguration;
  CItemMenu menu1_File_Loadconfiguration;
  CItemMenu pmenu2_Move;
  CItemMenu pmenu2_Delete;
  CPMenu menu1_Help;
  CItemMenu menu1_Help_Contents;
  CItemMenu menu1_Help_About;
  CFileDialog filedialog1;
  /*#Events*/
  void _EvOnCreate(CControl * control);
  void _EvOnShow(CControl * control);
  void _EvOnHide(CControl * control);
  void draw1_EvMouseMove(CControl * control,const uint button,const uint x,const uint y,const uint state);
  void draw1_EvMouseButtonPress(CControl * control,const uint button,const uint x,const uint y,const uint state);
  void draw1_EvMouseButtonRelease(CControl * control,const uint button,const uint x,const uint y,const uint state);
  void draw1_EvKeyboardPress(CControl * control,const uint key,const uint hkey ,const uint mask);
  void draw1_EvKeyboardRelease(CControl * control,const uint key,const uint hkey,const uint mask);
  void pmenu2_Properties_EvMenuActive(CControl * control);
  void timer1_EvOnTime(CControl * control);
  void menu1_File_Newconfiguration_EvMenuActive(CControl * control);
  void menu1_File_Saveconfiguration_EvMenuActive(CControl * control);
  void menu1_File_Loadconfiguration_EvMenuActive(CControl * control);
  void pmenu2_Move_EvMenuActive(CControl * control);
  void pmenu2_Delete_EvMenuActive(CControl * control);
  void menu1_Help_Contents_EvMenuActive(CControl * control);
  void menu1_Help_About_EvMenuActive(CControl * control);
  void filedialog1_EvOnClose(const int retId);
  
  /*#Others*/
  CPWindow5(void);
//lxrad automatic generated block end, don't edit above!
  void menu1_EvMenuActive(CControl * control);
  void Process(void);
  void PreProcess(void);
  void PostProcess(void);
  bool SaveConfig(String fname);
  bool LoadConfig(String fname);
  void DeleteParts(void);
  void WritePreferences(void);
  void ReadPreferences(char *name,char *value);
  void PropButtonRelease (CControl * control, uint button, uint x, uint y, uint state);
  void PropClose(int tag);
  void Set_i2c_bus(unsigned char pin, unsigned char value);
  unsigned char Get_i2c_bus(unsigned char pin);
  String GetPinsNames(void);
  String GetPinName(unsigned char pin);
  const picpin * GetPinsValues (void);
  void SetPin (unsigned char pin, unsigned char value);
  void WritePin (unsigned char pin, unsigned char value);
  void WritePinA (unsigned char pin, unsigned char avalue);
  void SetAPin (unsigned char pin, float value);
  unsigned char RegisterIOpin(String pname);
  private:
    board *pboard;
    String PinNames[256];
    picpin  * Pins;
    unsigned char PinsCount;
    unsigned char IOPinsCount;
    int partsc;  
    part *parts[MAX_PARTS];
    CItemMenu MParts[NUM_PARTS];
    String PartToCreate;
    int PartSelected;
    int PartToMove;
    int mdx,mdy;
    float scale;
    String LoadConfigFile;
    unsigned char i2c_bus[IOINIT];
    CPWindow wprop;
};

extern CPWindow5 Window5 ;

#endif /*#CPWINDOW5*/

