#include <stdio.h>
#include <pci/pci.h>

enum {
	DXIO_KPMX_MODE_GOP = 0,
};

void show_table (void)
{
	printf ("+-------+-------------------------------+-------------------------------+\n");
	printf ("|       |            Type B             |            Type A             |\n");
	printf ("+-------+-------+-------+-------+---+---+-------+-------+-------+---+---+\n");
	printf ("|       |   B4  |   B3  |   B2  | B1| B0|   A4  |   A3  |   A2  | A1| A0|\n");
	printf ("+-------+-------+-------+-------+---+---+-------+-------+-------+---+---+\n");
	printf ("| mode  |   P   |   P   |   P   | P | S |   G   |   G   |   G   | G | G |\n");
	printf ("+-------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf ("|       |1|1|1|1|1|1| | | | | | | | | | |1|1|1|1|1|1| | | | | | | | | | |\n");
	printf ("| lane  |5|4|3|2|1|0|9|8|7|6|5|4|3|2|1|0|5|4|3|2|1|0|9|8|7|6|5|4|3|2|1|0|\n");
	printf ("+-------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf ("| bif   |               16              |       8       |   4   | 2 |1|1|\n");
	printf ("+-------+-------------------------------+---------------+-------+---+-+-+\n");
	printf ("| width |               16              |       8       |   4   | 1 | | |\n");
	printf ("| speed |                               |               |       |   | | |\n");
	printf ("| slot  |               -               |       1       |   2   | - | | |\n");
	printf ("|       |                               |               |       |   | | |\n");
	printf ("|       |                               |               |       |   | | |\n");
	printf ("+-------+-------------------------------+---------------+-------+---+-+-+\n");

}

int main (int argc, char *argv[])
{
	struct pci_access *acc;

	acc = pci_alloc ();
	pci_init (acc);

	show_table ();

	pci_cleanup (acc);
	return 0;
}
