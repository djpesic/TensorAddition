#ifndef TENSORADDITIONKERNEL_H_
#define TENSORADDITIONKERNEL_H_

// #include "KernelManagerBlockSync.h"


namespace maxcompilersim {

class TensorAdditionKernel : public KernelManagerBlockSync {
public:
  TensorAdditionKernel(const std::string &instance_name);

protected:
  virtual void runComputationCycle();
  virtual void resetComputation();
  virtual void resetComputationAfterFlush();
          void updateState();
          void preExecute();
  virtual int  getFlushLevelStart();

private:
  t_port_number m_x;
  t_port_number m_y;
  t_port_number m_s;
  HWOffsetFix<1,0,UNSIGNED> id8out_io_s_force_disabled;

  HWOffsetFix<1,0,UNSIGNED> id0out_io_x_force_disabled;

  HWFloat<11,53> id2out_data;

  HWOffsetFix<1,0,UNSIGNED> id2st_read_next_cycle;
  HWFloat<11,53> id2st_last_read_value;

  HWOffsetFix<1,0,UNSIGNED> id3out_io_y_force_disabled;

  HWFloat<11,53> id5out_data;

  HWOffsetFix<1,0,UNSIGNED> id5st_read_next_cycle;
  HWFloat<11,53> id5st_last_read_value;

  HWFloat<11,53> id6out_result[13];

  HWOffsetFix<1,0,UNSIGNED> id16out_value;

  HWOffsetFix<1,0,UNSIGNED> id25out_value;

  HWOffsetFix<49,0,UNSIGNED> id13out_value;

  HWOffsetFix<48,0,UNSIGNED> id14out_count;
  HWOffsetFix<1,0,UNSIGNED> id14out_wrap;

  HWOffsetFix<49,0,UNSIGNED> id14st_count;

  HWOffsetFix<1,0,UNSIGNED> id24out_value;

  HWOffsetFix<49,0,UNSIGNED> id19out_value;

  HWOffsetFix<48,0,UNSIGNED> id20out_count;
  HWOffsetFix<1,0,UNSIGNED> id20out_wrap;

  HWOffsetFix<49,0,UNSIGNED> id20st_count;

  HWOffsetFix<48,0,UNSIGNED> id22out_run_cycle_count;

  HWOffsetFix<1,0,UNSIGNED> id23out_result[2];

  const HWOffsetFix<1,0,UNSIGNED> c_hw_fix_1_0_uns_bits;
  const HWFloat<11,53> c_hw_flt_11_53_undef;
  const HWOffsetFix<1,0,UNSIGNED> c_hw_fix_1_0_uns_bits_1;
  const HWOffsetFix<49,0,UNSIGNED> c_hw_fix_49_0_uns_bits;
  const HWOffsetFix<49,0,UNSIGNED> c_hw_fix_49_0_uns_bits_1;
  const HWOffsetFix<49,0,UNSIGNED> c_hw_fix_49_0_uns_bits_2;

  void execute0();
};

}

#endif /* TENSORADDITIONKERNEL_H_ */
