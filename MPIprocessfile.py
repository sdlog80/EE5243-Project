#MPIprocessfile.py
from mpi4py import MPI 
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

print "Hello world from process %d out of %d! " % (rank, size)
