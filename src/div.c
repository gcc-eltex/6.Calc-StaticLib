double div(double first, double second, int *error){
	if(second == 0){
		*error = -1;
		return 0;
	}
	return first / second;
}