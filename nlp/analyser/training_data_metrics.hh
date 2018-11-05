//
// Created by c on 05/11/2018 17:43
//

#ifndef NLP_ANALYSER_TRAINING_DATA_METRICS_HH
#define NLP_ANALYSER_TRAINING_DATA_METRICS_HH

/* include section */

#include <map>
#include "analyser/reader.hh"
#include "analyser/tokenizer.hh"

/* class & function section */

namespace nlp {

/* metrics struct for training data */
struct TrainingDataMetrics {
	Index number_of_samples;
	Index number_of_classes;
	Index number_of_tokens;
	Index sample_length_block_size = 10; // default value
	std::vector<Index> number_of_samples_per_class;
	std::vector<Index> distribution_of_sample_length;

	TrainingDataMetrics() = default;
};


/* collect training data info */
template<READER_TYPE RT, CUT_TYPE CT>
TrainingDataMetrics collect_training_data_info(std::string const& fn, Tokenizer<CT> const& tokenizer) {
	static_assert(RT != READER_TYPE::UNLABELED,
			"analyse only for labeled data.");
	TrainingDataMetrics tdm;
	Reader<RT> reader{fn};

	// statistic
	std::map<std::string, Index> count_label;
	std::map<std::string, Index> count_token;

	std::string text;
	typename Reader<RT>::label_t label;
	while (!reader.eof()) {
		if (reader.readline(text, label)) {
			// increase number of samples
			++tdm.number_of_samples;

			// update number of classes
			if constexpr (RT == READER_TYPE::LABELED) {
				++count_label[label];
			} else if constexpr (RT == READER_TYPE::MULTI_LABELED){
				for (auto& l : label) ++count_label[l];
			} else {
			}

			auto tokens = tokenizer.cut(text);
			// update number of tokens
			for (auto& t : tokens) ++count_token[t];

			// update distribution of sample length
			Index idx = tokens.size() / tdm.sample_length_block_size;
			if (idx >= tdm.distribution_of_sample_length.size())
				tdm.distribution_of_sample_length.resize(idx + 1, 0);
			++tdm.distribution_of_sample_length[idx];
		}
	}

	// final calculate number of classes & tokens
	tdm.number_of_classes = count_label.size();
	tdm.number_of_tokens = count_token.size();

	// update number of samples per class
	for (auto& x : count_label)
		tdm.number_of_samples_per_class.push_back(x.second);

	return tdm;
}

} // namespace nlp

#endif//


