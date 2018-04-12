#include <stdio.h>
#include <string.h>
#include <pci/pci.h>

#define MAX_PHY          10
#define MAX_LANE_PER_DIE 32

enum {
	DXIO_KPMX_MODE_UNSET = 0,
	DXIO_KPMX_MODE_GOP,
	DXIO_KPMX_MODE_PCIE,
	DXIO_KPMX_MODE_SATA,
	DXIO_KPMX_MODE_XGBE,
	DXIO_KPMX_MODE_MAX,
};
const char dxio_kpmx_mode_name[] = " GPSX";
#define DXIO_MODE_NAME(i) (dxio_kpmx_mode_name[i])

typedef struct {
	uint8_t  Socket;
	uint8_t  Die;
	uint8_t  Mode[MAX_PHY];
	uint8_t  Enable[MAX_LANE_PER_DIE];
	uint8_t  Bifurcation[MAX_LANE_PER_DIE];
	uint8_t  Width[MAX_LANE_PER_DIE];
	uint8_t  Speed[MAX_LANE_PER_DIE];
	uint8_t  Slot[MAX_LANE_PER_DIE];
} DXIO_STATUS;

/*
 * +-------+-------------------------------+-------------------------------+
 * |       |            Type B             |            Type A             |
 * +-------+-------+-------+-------+---+---+-------+-------+-------+---+---+
 * |       |   B4  |   B3  |   B2  | B1| B0|   A4  |   A3  |   A2  | A1| A0|
 * +-------+-------+-------+-------+---+---+-------+-------+-------+---+---+
 * | Mode  |   P   |   P   |   P   | P | S |   G   |   G   |   G   | G | G |
 * +-------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * |       |1|1|1|1|1|1| | | | | | | | | | |1|1|1|1|1|1| | | | | | | | | | |
 * | Lane  |5|4|3|2|1|0|9|8|7|6|5|4|3|2|1|0|5|4|3|2|1|0|9|8|7|6|5|4|3|2|1|0|
 * +-------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | Enable|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|1|
 * +-------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
 * | Bif   |               16              |       8       |   4   | 2 |1|1|
 * +-------+-------------------------------+---------------+-------+---+-+-+
 * | Width |               16              |       8       |   4   | 1 | | |
 * | Speed |                               |               |       |   | | |
 * | Slot  |               -               |       1       |   2   | - | | |
 * +-------+-------------------------------+---------------+-------+---+-+-+
 */
void show_table (DXIO_STATUS *d)
{
	uint8_t index;

	printf ("+-------+-------------------------------+-------------------------------+\n");
	printf ("|       |            Type B             |            Type A             |\n");
	printf ("+-------+-------+-------+-------+---+---+-------+-------+-------+---+---+\n");
	printf ("|       |   B4  |   B3  |   B2  | B1| B0|   A4  |   A3  |   A2  | A1| A0|\n");
	printf ("+-------+-------+-------+-------+---+---+-------+-------+-------+---+---+\n");
	printf ("| Mode  |   %c   |   %c   |   %c   | %c | %c |   %c   |   %c   |   %c   | %c | %c |\n",
		DXIO_MODE_NAME(d->Mode[9]), DXIO_MODE_NAME(d->Mode[8]), DXIO_MODE_NAME(d->Mode[7]),
		DXIO_MODE_NAME(d->Mode[6]), DXIO_MODE_NAME(d->Mode[5]), DXIO_MODE_NAME(d->Mode[4]),
		DXIO_MODE_NAME(d->Mode[3]), DXIO_MODE_NAME(d->Mode[2]), DXIO_MODE_NAME(d->Mode[1]),
		DXIO_MODE_NAME(d->Mode[0])
		);
	printf ("+-------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf ("|       |1|1|1|1|1|1| | | | | | | | | | |1|1|1|1|1|1| | | | | | | | | | |\n");
	printf ("| Lane  |5|4|3|2|1|0|9|8|7|6|5|4|3|2|1|0|5|4|3|2|1|0|9|8|7|6|5|4|3|2|1|0|\n");
	printf ("+-------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf ("| Enable|");
	for (index = 0; index < MAX_LANE_PER_DIE; index++) {
		printf ("%d|", d->Enable[MAX_LANE_PER_DIE - 1 - index]);
	}
	printf ("\n");
	printf ("+-------+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf ("| Bif   |               16              |       8       |   4   | 2 |1|1|\n");
	printf ("+-------+-------------------------------+---------------+-------+---+-+-+\n");
	printf ("| Width |               16              |       8       |   4   | 1 | | |\n");
	printf ("| Speed |                               |               |       |   | | |\n");
	printf ("| Slot  |               -               |       1       |   2   | - | | |\n");
	printf ("+-------+-------------------------------+---------------+-------+---+-+-+\n");
}

void demo (void)
{
	DXIO_STATUS dxio_status;

	memset (&dxio_status, 0, sizeof (DXIO_STATUS));
	show_table (&dxio_status);
}

int main (int argc, char *argv[])
{
	struct pci_access *acc;

	acc = pci_alloc ();
	pci_init (acc);

	demo ();

	pci_cleanup (acc);
	return 0;
}
