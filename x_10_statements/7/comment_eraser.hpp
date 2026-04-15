#ifndef DV_COMMENT_ERASER_HPP
#define DV_COMMENT_ERASER_HPP
#include <iterator>
#include <iostream>
using namespace std;

namespace dv_comment_eraser {
	enum class state {
		code,
		presumably_comment,
		ml_comment,
		sl_comment,
		quote,
		presumably_stop_ml_comment,
		presumably_ml_comment_error,
		presumably_sl_comment_error,
		comment_error,
		finish
	};

	struct context {
		istream_iterator<char> cursor;
		state cur_state;
	}
	
	void erase(context* ctx, ostream& os);
}

using namespace dv_comment_eraser;

void 

void erase_from_input(context* ctx, ostream& os) {
	while(ctx -> cur_state != state::finish) {
			
	}
}

#endif
