double deadband(double x, double band)
{
	if(x<0)
	{
		x = (x+deadband)/(1-deadband);
		return x < 0 ? x : 0;
	}
	else
	{
		x = (x-deadband)/(1-deadband);
		return x > 0 ? x : 0;
	}
}
