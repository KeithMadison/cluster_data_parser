#ifndef TOOLS_H_INCLUDED
#define TOOLS_H_INCLUDED

std::vector<double>::iterator search(std::vector<double> &vec, double value){
	
	auto it = lower_bound(vec.begin(), vec.end(), value);

	if(it != vec.begin()){

		if(std::abs(value - *(it - 1)) <  std::abs(value - *it)){
			--it;
		}

	}

	return it;

}

struct scorecard{
	double score;
	int previous;
};

#define infty std::numeric_limits<double>::infinity()

/*** docstring ***/

vector<double> subsequence(double period, double threshold, vector<double> times){

	vector<double> filtered;
	vector<scorecard> bests = {{0,-1}};

	for(int i = 1; i < times.size(); ++i){

		scorecard best = {infty, -1};

		for(int j = i; j > -1; --j){

			const double delta = times[i] - times[j];
			const double penalty = pow(delta - period, 2);

			if(abs(delta - period) < threshold)
				filtered.push_back(times[i]);

			if(delta >= period && penalty >= best.score) 
				break;

			if(bests[j].score + penalty < best.score)
				best = {bests[j].score + penalty, j};

		}

		bests.push_back(best);

	}

	return filtered;

}



#endif
