#include "stdsimheader.h"
//#define BOOST_NO_STD_LOCALE
//#include <boost/format.hpp>

//#include "TensorAdditionKernel.h"

namespace maxcompilersim {

void TensorAdditionKernel::execute0() {
  { // Node ID: 8 (NodeInputMappedReg)
  }
  HWOffsetFix<1,0,UNSIGNED> id9out_result;

  { // Node ID: 9 (NodeNot)
    const HWOffsetFix<1,0,UNSIGNED> &id9in_a = id8out_io_s_force_disabled;

    id9out_result = (not_fixed(id9in_a));
  }
  { // Node ID: 0 (NodeInputMappedReg)
  }
  HWOffsetFix<1,0,UNSIGNED> id1out_result;

  { // Node ID: 1 (NodeNot)
    const HWOffsetFix<1,0,UNSIGNED> &id1in_a = id0out_io_x_force_disabled;

    id1out_result = (not_fixed(id1in_a));
  }
  if ( (getFillLevel() >= (4l)))
  { // Node ID: 2 (NodeInput)
    const HWOffsetFix<1,0,UNSIGNED> &id2in_enable = id1out_result;

    (id2st_read_next_cycle) = ((id2in_enable.getValueAsBool())&(!(((getFlushLevel())>=(4l))&(isFlushingActive()))));
    queueReadRequest(m_x, id2st_read_next_cycle.getValueAsBool());
  }
  { // Node ID: 3 (NodeInputMappedReg)
  }
  HWOffsetFix<1,0,UNSIGNED> id4out_result;

  { // Node ID: 4 (NodeNot)
    const HWOffsetFix<1,0,UNSIGNED> &id4in_a = id3out_io_y_force_disabled;

    id4out_result = (not_fixed(id4in_a));
  }
  if ( (getFillLevel() >= (4l)))
  { // Node ID: 5 (NodeInput)
    const HWOffsetFix<1,0,UNSIGNED> &id5in_enable = id4out_result;

    (id5st_read_next_cycle) = ((id5in_enable.getValueAsBool())&(!(((getFlushLevel())>=(4l))&(isFlushingActive()))));
    queueReadRequest(m_y, id5st_read_next_cycle.getValueAsBool());
  }
  { // Node ID: 6 (NodeAdd)
    const HWFloat<11,53> &id6in_a = id2out_data;
    const HWFloat<11,53> &id6in_b = id5out_data;

    id6out_result[(getCycle()+12)%13] = (add_float(id6in_a,id6in_b));
  }
  if ( (getFillLevel() >= (21l)) && (getFlushLevel() < (21l)|| !isFlushingActive() ))
  { // Node ID: 11 (NodeOutput)
    const HWOffsetFix<1,0,UNSIGNED> &id11in_output_control = id9out_result;
    const HWFloat<11,53> &id11in_data = id6out_result[getCycle()%13];

    bool id11x_1;

    (id11x_1) = ((id11in_output_control.getValueAsBool())&(!(((getFlushLevel())>=(21l))&(isFlushingActive()))));
    if((id11x_1)) {
      writeOutput(m_s, id11in_data);
    }
  }
  { // Node ID: 16 (NodeConstantRawBits)
  }
  { // Node ID: 25 (NodeConstantRawBits)
  }
  { // Node ID: 13 (NodeConstantRawBits)
  }
  if ( (getFillLevel() >= (3l)))
  { // Node ID: 14 (NodeCounterV1)
    const HWOffsetFix<1,0,UNSIGNED> &id14in_enable = id25out_value;
    const HWOffsetFix<49,0,UNSIGNED> &id14in_max = id13out_value;

    HWOffsetFix<49,0,UNSIGNED> id14x_1;
    HWOffsetFix<1,0,UNSIGNED> id14x_2;
    HWOffsetFix<1,0,UNSIGNED> id14x_3;
    HWOffsetFix<49,0,UNSIGNED> id14x_4t_1e_1;

    id14out_count = (cast_fixed2fixed<48,0,UNSIGNED,TRUNCATE>((id14st_count)));
    (id14x_1) = (add_fixed<49,0,UNSIGNED,TRUNCATE>((id14st_count),(c_hw_fix_49_0_uns_bits_2)));
    (id14x_2) = (gte_fixed((id14x_1),id14in_max));
    (id14x_3) = (and_fixed((id14x_2),id14in_enable));
    id14out_wrap = (id14x_3);
    if((id14in_enable.getValueAsBool())) {
      if(((id14x_3).getValueAsBool())) {
        (id14st_count) = (c_hw_fix_49_0_uns_bits_1);
      }
      else {
        (id14x_4t_1e_1) = (id14x_1);
        (id14st_count) = (id14x_4t_1e_1);
      }
    }
    else {
    }
  }
  HWOffsetFix<48,0,UNSIGNED> id15out_output;

  { // Node ID: 15 (NodeStreamOffset)
    const HWOffsetFix<48,0,UNSIGNED> &id15in_input = id14out_count;

    id15out_output = id15in_input;
  }
  if ( (getFillLevel() >= (4l)) && (getFlushLevel() < (4l)|| !isFlushingActive() ))
  { // Node ID: 17 (NodeOutputMappedReg)
    const HWOffsetFix<1,0,UNSIGNED> &id17in_load = id16out_value;
    const HWOffsetFix<48,0,UNSIGNED> &id17in_data = id15out_output;

    bool id17x_1;

    (id17x_1) = ((id17in_load.getValueAsBool())&(!(((getFlushLevel())>=(4l))&(isFlushingActive()))));
    if((id17x_1)) {
      setMappedRegValue("current_run_cycle_count", id17in_data);
    }
  }
  { // Node ID: 24 (NodeConstantRawBits)
  }
  { // Node ID: 19 (NodeConstantRawBits)
  }
  if ( (getFillLevel() >= (0l)))
  { // Node ID: 20 (NodeCounterV1)
    const HWOffsetFix<1,0,UNSIGNED> &id20in_enable = id24out_value;
    const HWOffsetFix<49,0,UNSIGNED> &id20in_max = id19out_value;

    HWOffsetFix<49,0,UNSIGNED> id20x_1;
    HWOffsetFix<1,0,UNSIGNED> id20x_2;
    HWOffsetFix<1,0,UNSIGNED> id20x_3;
    HWOffsetFix<49,0,UNSIGNED> id20x_4t_1e_1;

    id20out_count = (cast_fixed2fixed<48,0,UNSIGNED,TRUNCATE>((id20st_count)));
    (id20x_1) = (add_fixed<49,0,UNSIGNED,TRUNCATE>((id20st_count),(c_hw_fix_49_0_uns_bits_2)));
    (id20x_2) = (gte_fixed((id20x_1),id20in_max));
    (id20x_3) = (and_fixed((id20x_2),id20in_enable));
    id20out_wrap = (id20x_3);
    if((id20in_enable.getValueAsBool())) {
      if(((id20x_3).getValueAsBool())) {
        (id20st_count) = (c_hw_fix_49_0_uns_bits_1);
      }
      else {
        (id20x_4t_1e_1) = (id20x_1);
        (id20st_count) = (id20x_4t_1e_1);
      }
    }
    else {
    }
  }
  { // Node ID: 22 (NodeInputMappedReg)
  }
  { // Node ID: 23 (NodeEq)
    const HWOffsetFix<48,0,UNSIGNED> &id23in_a = id20out_count;
    const HWOffsetFix<48,0,UNSIGNED> &id23in_b = id22out_run_cycle_count;

    id23out_result[(getCycle()+1)%2] = (eq_fixed(id23in_a,id23in_b));
  }
  if ( (getFillLevel() >= (1l)))
  { // Node ID: 21 (NodeFlush)
    const HWOffsetFix<1,0,UNSIGNED> &id21in_start = id23out_result[getCycle()%2];

    if((id21in_start.getValueAsBool())) {
      startFlushing();
    }
  }
};

};
