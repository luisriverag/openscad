#include "io/imageutils.h"

#include <iostream>
#include <vector>

#include "lodepng/lodepng.h"

bool write_png(std::ostream& output, unsigned char *pixels, int width, int height)
{
  std::vector<unsigned char> dataout;
  lodepng::State state;
  state.encoder.auto_convert = false;
  // some png renderers have different interpretations of alpha, so don't use it
  state.info_png.color.colortype = LCT_RGB;
  state.info_png.color.bitdepth = 8;
  const auto err = lodepng::encode(dataout, pixels, width, height, state);
  if (err) return false;
  output.write(reinterpret_cast<const char *>(&dataout[0]), dataout.size());
  if (output.bad() ) std::cerr << "Error writing to ostream\n";
  return output.good();
}
