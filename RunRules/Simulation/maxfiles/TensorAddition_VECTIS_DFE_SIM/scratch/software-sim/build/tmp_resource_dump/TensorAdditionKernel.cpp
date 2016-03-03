#include "stdsimheader.h"
#include "TensorAdditionKernel.h"

namespace maxcompilersim {

TensorAdditionKernel::TensorAdditionKernel(const std::string &instance_name) : 
  ManagerBlockSync(instance_name),
  KernelManagerBlockSync(instance_name, 21, 2, 0, 0, "",1)
, c_hw_fix_1_0_uns_bits((HWOffsetFix<1,0,UNSIGNED>(varint_u<1>(0x0l))))
, c_hw_flt_11_53_undef((HWFloat<11,53>()))
, c_hw_fix_1_0_uns_bits_1((HWOffsetFix<1,0,UNSIGNED>(varint_u<1>(0x1l))))
, c_hw_fix_49_0_uns_bits((HWOffsetFix<49,0,UNSIGNED>(varint_u<49>(0x1000000000000l))))
, c_hw_fix_49_0_uns_bits_1((HWOffsetFix<49,0,UNSIGNED>(varint_u<49>(0x0000000000000l))))
, c_hw_fix_49_0_uns_bits_2((HWOffsetFix<49,0,UNSIGNED>(varint_u<49>(0x0000000000001l))))
{
  { // Node ID: 8 (NodeInputMappedReg)
    registerMappedRegister("io_s_force_disabled", Data(1));
  }
  { // Node ID: 0 (NodeInputMappedReg)
    registerMappedRegister("io_x_force_disabled", Data(1));
  }
  { // Node ID: 2 (NodeInput)
     m_x =  registerInput("x",0,5);
  }
  { // Node ID: 3 (NodeInputMappedReg)
    registerMappedRegister("io_y_force_disabled", Data(1));
  }
  { // Node ID: 5 (NodeInput)
     m_y =  registerInput("y",1,5);
  }
  { // Node ID: 11 (NodeOutput)
    m_s = registerOutput("s",0 );
  }
  { // Node ID: 16 (NodeConstantRawBits)
    id16out_value = (c_hw_fix_1_0_uns_bits_1);
  }
  { // Node ID: 25 (NodeConstantRawBits)
    id25out_value = (c_hw_fix_1_0_uns_bits_1);
  }
  { // Node ID: 13 (NodeConstantRawBits)
    id13out_value = (c_hw_fix_49_0_uns_bits);
  }
  { // Node ID: 17 (NodeOutputMappedReg)
    registerMappedRegister("current_run_cycle_count", Data(48), true);
  }
  { // Node ID: 24 (NodeConstantRawBits)
    id24out_value = (c_hw_fix_1_0_uns_bits_1);
  }
  { // Node ID: 19 (NodeConstantRawBits)
    id19out_value = (c_hw_fix_49_0_uns_bits);
  }
  { // Node ID: 22 (NodeInputMappedReg)
    registerMappedRegister("run_cycle_count", Data(48));
  }
}

void TensorAdditionKernel::resetComputation() {
  resetComputationAfterFlush();
}

void TensorAdditionKernel::resetComputationAfterFlush() {
  { // Node ID: 8 (NodeInputMappedReg)
    id8out_io_s_force_disabled = getMappedRegValue<HWOffsetFix<1,0,UNSIGNED> >("io_s_force_disabled");
  }
  { // Node ID: 0 (NodeInputMappedReg)
    id0out_io_x_force_disabled = getMappedRegValue<HWOffsetFix<1,0,UNSIGNED> >("io_x_force_disabled");
  }
  { // Node ID: 2 (NodeInput)

    (id2st_read_next_cycle) = (c_hw_fix_1_0_uns_bits);
    (id2st_last_read_value) = (c_hw_flt_11_53_undef);
  }
  { // Node ID: 3 (NodeInputMappedReg)
    id3out_io_y_force_disabled = getMappedRegValue<HWOffsetFix<1,0,UNSIGNED> >("io_y_force_disabled");
  }
  { // Node ID: 5 (NodeInput)

    (id5st_read_next_cycle) = (c_hw_fix_1_0_uns_bits);
    (id5st_last_read_value) = (c_hw_flt_11_53_undef);
  }
  { // Node ID: 14 (NodeCounterV1)

    (id14st_count) = (c_hw_fix_49_0_uns_bits_1);
  }
  { // Node ID: 20 (NodeCounterV1)

    (id20st_count) = (c_hw_fix_49_0_uns_bits_1);
  }
  { // Node ID: 22 (NodeInputMappedReg)
    id22out_run_cycle_count = getMappedRegValue<HWOffsetFix<48,0,UNSIGNED> >("run_cycle_count");
  }
}

void TensorAdditionKernel::updateState() {
  { // Node ID: 8 (NodeInputMappedReg)
    id8out_io_s_force_disabled = getMappedRegValue<HWOffsetFix<1,0,UNSIGNED> >("io_s_force_disabled");
  }
  { // Node ID: 0 (NodeInputMappedReg)
    id0out_io_x_force_disabled = getMappedRegValue<HWOffsetFix<1,0,UNSIGNED> >("io_x_force_disabled");
  }
  { // Node ID: 3 (NodeInputMappedReg)
    id3out_io_y_force_disabled = getMappedRegValue<HWOffsetFix<1,0,UNSIGNED> >("io_y_force_disabled");
  }
  { // Node ID: 22 (NodeInputMappedReg)
    id22out_run_cycle_count = getMappedRegValue<HWOffsetFix<48,0,UNSIGNED> >("run_cycle_count");
  }
}

void TensorAdditionKernel::preExecute() {
  { // Node ID: 2 (NodeInput)
    if(((needsToReadInput(m_x))&(((getFlushLevel())<((4l)+(5)))|(!(isFlushingActive()))))) {
      (id2st_last_read_value) = (readInput<HWFloat<11,53> >(m_x));
    }
    id2out_data = (id2st_last_read_value);
  }
  { // Node ID: 5 (NodeInput)
    if(((needsToReadInput(m_y))&(((getFlushLevel())<((4l)+(5)))|(!(isFlushingActive()))))) {
      (id5st_last_read_value) = (readInput<HWFloat<11,53> >(m_y));
    }
    id5out_data = (id5st_last_read_value);
  }
}

void TensorAdditionKernel::runComputationCycle() {
  if (m_mappedElementsChanged) {
    m_mappedElementsChanged = false;
    updateState();
    std::cout << "TensorAdditionKernel: Mapped Elements Changed: Reloaded" << std::endl;
  }
  preExecute();
  execute0();
}

int TensorAdditionKernel::getFlushLevelStart() {
  return ((1l)+(3l));
}

}
