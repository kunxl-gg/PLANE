/**
 * An interface to implement each block in the pipeline.
 * Any new block that needs to be added to the pipeline needs to inherit this block
 */

class IProcessBlock {
public:
	virtual ~IProcessBlock() = default;

	/**
	 * The execute method will be called at each iteration of the pipeline.
	 * Each block is responsible for reading the input processing the data,
	 * and then forwarding the output to the next block.
	 */
	virtual void execute() = 0;
};
