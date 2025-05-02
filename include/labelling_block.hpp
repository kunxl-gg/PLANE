#ifndef LABELLING_BLOCK_H
#define LABELLING_BLOCK_H

#include "include/iprocess_block.hpp"

class LabellingBlock : public IProcessBlock {
public:
	~LabellingBlock();
	virtual void execute() override;
};

#endif // LABELLING_BLOCK_H
