//Geometry definition
struct ce_cord{
	double x;
	double y;
};
struct ce_size{
	double width;
	double height;
};
struct ce_rect{
	ce_cord cord;
	ce_size size;
};

//Creating geometry
ce_cord makeCord(double x, double y);
ce_size makeSize(double width, double height);
ce_rect makeRect(double x, double y, double width, double height);

//Level grid type definition
enum grid_type { cet_blank = 0, cet_wall = 1, cet_ladder = 2, cet_egg = 3, cet_grain = 4, cet_inv_wall = 5, cet_sol_ladder = 6 };