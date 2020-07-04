# Statistics

# Prerequisites Libraries
1- boost 

Calculate stats on Streaming data \n
 1- Mean \n
 2- Variance \n 
 3- Standard Deviation \n

Example Usage:

RunningStatsCalculator running = RunningStatsCalculator();
	running.update(1);
	running.update(2);
	running.update(3);

	cout<<"running mean = "<< running.mean()<<"\n";
	cout<<"running pop variance = "<< running.populationVariance()<<"\n";
	cout<<"running pop stdev = "<< running.populationStdev()<<"\n";
	cout<<"running sample variance = "<< running.sampleVariance()<<"\n";
	cout<<"running sample stdev = "<< running.sampleStdev()<<"\n";

To Calculate on Window based Streaming data Use RunningWindowStatsCalculator(windowSize) 
