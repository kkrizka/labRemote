#include "AMAC.h"

#include <unistd.h>

AMAC::AMAC(unsigned short amacid, std::unique_ptr<EndeavourRaw> raw)
  : EndeavourCom(amacid, std::move(raw)), AMACv2Reg()
{ }

AMAC::~AMAC(){}

void AMAC::init()
{
  // Set AMAC ID
  //EndeavourCom::setid(EndeavourCom::REFMODE::IDPads, 0x1F);
  usleep(10);

  // Read AMAC registers into memory
  uint data;
  for(uint reg=0;reg<AMACv2Reg::numRegs;reg++)
    {
      data=(reg==0)?read_reg(reg):readnext_reg();
      setReg(reg, data);
      usleep(10);
    }

  // Set ideal settings
  wrField(&AMACv2Reg::VDDbg, 13); // Set VDD to 1.2V

  // for (auto const& p : regMap)
  //   { //set all amac registers according to default values
  //     if(canBeWritten(p.second))
  // 	syncReg(p.second);
  //   }  
}

void AMAC::syncReg(AMACv2Field AMACv2Reg::* ref)
{
  EndeavourCom::write_reg(getAddr(ref), (this->*ref).readRaw());
}

void AMAC::wrField(AMACv2Field AMACv2Reg::* ref, uint32_t data)
{
  setField(ref, data);
  EndeavourCom::write_reg(getAddr(ref), (this->*ref).readRaw());
  usleep(10);
}

uint32_t AMAC::rdField(AMACv2Field AMACv2Reg::* ref)
{
  uint32_t ret = EndeavourCom::read_reg(getAddr(ref));  
  setReg(getAddr(ref), ret);
  usleep(10);
  return getField(ref);
}

void AMAC::write_reg(unsigned int address, unsigned int data)
{
  setReg(address, data);
  EndeavourCom::write_reg(address, data);
  usleep(10);
}