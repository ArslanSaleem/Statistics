//============================================================================
// Name        : Statistics.cpp
// Author      : Arslan Saleem
//============================================================================

#include <iostream>
#include <cmath>
#include <ctime>
#include <boost/circular_buffer.hpp>
using namespace std;

class RunningStatsCalculator {

private:
	long int count = 0; // long in case of window size not specified
	float runningMean = 0.f;
	float dSquaredValue = 0.f;
public:
	RunningStatsCalculator() {
	}

	void update(float newValue) {
		count++;
		float meanDifferential = (newValue - runningMean) / count;
		float newMean = runningMean + meanDifferential;
		float dSquaredIncrement = (newValue - newMean) * (newValue - runningMean);
		dSquaredValue += dSquaredIncrement;
		runningMean = newMean;
	}

	float mean() {
		return validate()? runningMean: 0.f;
	}

	float populationVariance() {
		return dSquaredValue / count;
	}

	float populationStdev() {
		return sqrt(populationVariance());
	}

	float sampleVariance() {
		return count > 1 ? dSquaredValue / (count - 1) : 0;
	}

	float sampleStdev() {
		return sqrt(sampleVariance());
	}

	bool validate() {
		return count==0? false: true;
	}
};


class RunningWindowStatsCalculator {

private:
	long int count = 0; // long in case of window size not specified
	float runningMean = 0.f;
	float dSquaredValue = 0.f;
	float windowSize = 0.f;
	boost::circular_buffer<float> circularBuffer;
public:
	RunningWindowStatsCalculator(int winSize) {
		circularBuffer = boost::circular_buffer<float>(windowSize);
		windowSize = winSize;
	}

	void update(float newValue) {
		if (count!=windowSize){count++;}
		float poppedValue = circularBuffer.front();
		float meanDifferential = (newValue - poppedValue) / count;
		float newMean = runningMean + meanDifferential;
		float dSquaredIncrement = ((newValue - poppedValue)*(newValue - newMean + poppedValue - runningMean));
		dSquaredValue += dSquaredIncrement;
		runningMean = newMean;
		circularBuffer.push_back(newValue);
	}

	float mean() {
		return validate()? runningMean: 0.f;
	}

	float populationVariance() {
		return dSquaredValue / count;
	}

	float populationStdev() {
		return sqrt(populationVariance());
	}

	float sampleVariance() {
		return count > 1 ? dSquaredValue / (count - 1) : 0;
	}

	float sampleStdev() {
		return sqrt(sampleVariance());
	}

	bool validate() {
		return count==0? false: true;
	}
};



int main() {
	RunningStatsCalculator running = RunningStatsCalculator();
	running.update(1);
	running.update(2);
	running.update(3);

	cout<<"running mean = "<< running.mean()<<"\n";
	cout<<"running pop variance = "<< running.populationVariance()<<"\n";
	cout<<"running pop stdev = "<< running.populationStdev()<<"\n";
	cout<<"running sample variance = "<< running.sampleVariance()<<"\n";
	cout<<"running sample stdev = "<< running.sampleStdev()<<"\n";

	return 0;
}
