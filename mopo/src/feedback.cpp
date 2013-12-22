/* Copyright 2013 Little IO
 *
 * mopo is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * mopo is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with mopo.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "feedback.h"

#include "processor_router.h"

namespace mopo {

  void Feedback::process() {
    memcpy(buffer_, inputs_[0]->source->buffer,
           BUFFER_SIZE * sizeof(mopo_float));
    refreshOutput();
  }

  void Feedback::refreshOutput() {
    memcpy(outputs_[0]->buffer, buffer_, BUFFER_SIZE * sizeof(mopo_float));
  }

  void Feedback::tick(int i) {
    buffer_[i] = inputs_[0]->source->buffer[i];
  }

  void Feedback::tickBeginRefreshOutput() {
    outputs_[0]->buffer[0] = buffer_[BUFFER_SIZE - 1];
  }

  void Feedback::tickRefreshOutput(int i) {
    MOPO_ASSERT(i > 0 && i < i < BUFFER_SIZE);
    outputs_[0]->buffer[i] = buffer_[i - 1];
  }
} // namespace mopo
