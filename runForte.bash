#!/bin/bash
#SBATCH --qos bbshort
#SBATCH --ntasks=1
#SBATCH --account=mangers-positron-imaging-centre
#SBATCH --time 0:10:00
#SBATCH --mem=10G
#SBATCH --mail-type FAIL

set -e

module purge; module load bluebear

module load bear-apps/2020a
module load foss/2020a
module load CMake/3.16.4-GCCcore-9.3.0
module load GCC/9.3.0
module load ROOT/6.20.00-foss-2019b-Python-3.7.4


source /rds/projects/m/mangers-positron-imaging-centre/root/install/bin/thisroot.sh
source /rds/projects/m/mangers-positron-imaging-centre/geant4/install/bin/geant4.sh
export PATH=$PATH:/rds/projects/m/mangers-positron-imaging-centre/gate/install/bin

# Time = simulation duration in seconds
# Act = source activity in MBq
# x, y, z = source position
# sep = head seperation in mm. User must add 87 mm to get desired seperatioon
# Example: to get 600 mm total seperation each head must be moved 300 mm, plus 87 mm for the offset in the model
# Thus, "sep" should equal 387 mm
# outname = name of desired outfile

Gate -a [Time,$1][Act,$2][x,$3][y,$4][z,$5][sep,$6][outname,$7] runForte.mac

