/*
 * Copyright (C) 2016 Sensative AB
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <iostream>
#include <set>
#include "system.hpp"
#include "sfr.hpp"
#include "alu.hpp"
#include "block.hpp"

CLKSEL::CLKSEL(std::string name, Block &block, std::uint8_t address, std::uint8_t resetValue, std::set<std::uint8_t> pages):
  Sfr(name, block, address, resetValue, pages)
{
}

std::uint8_t CLKSEL::Read()
{
  // Let's always assume the clock is valid
  return data | 0x80;
}

System::System(std::string name, Scheduler &s, Alu &a) :
  Block(name, s, a),
  clksel("CLKSEL", *this, 0xa9, 0x82, {0x0, 0xf}),
  oscicn("OSCICN", *this, 0xb2, 0x00, {0x0}),
  rstsrc("RSTSRC", *this, 0xef, 0x00, {0x0}),
  ref0cn("REF0CN", *this, 0xd1, 0x18, {0x0}),
  rtc0key("RTC0KEY", *this, 0xae, 0x00, {0x0}),
  rtc0dat("RTC0DAT", *this, 0xad, 0x00, {0x0}),
  rtc0adr("RTC0ADR", *this, 0xac, 0x00, {0x0}),
  pmu0cf("PMU0CF", *this, 0xb5, 0x00, {0x0}),
  reg0cn("REG0CN", *this, 0xc9, 0x00, {0x0}),
  vdm0cn("VCM0CN", *this, 0xff, 0x88, {0x0})
{
}
