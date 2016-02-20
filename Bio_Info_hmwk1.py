from Bio import Entrez
from Bio import Seqio
from Bio.SubsMat import MatrixInfo
import os.path 
import sys
#the match score MATCH, mismatch 
#score MISMATCH and the DNA gap penalty DGAP, 
#and the protein gap penalty PGAP
def main():
	human = './RC417443.1.gb'
	human_file = 'RC417443.1.gb'
	match_score = int(sys.argv[1])
	mismatch_score = int(sys.argv[2])
	DNA_gap_penalty = int(sys.argv[3])
	Protein_gap_penalty = int(sys.argv[4])
	Entrez.email = "shoyeb@rpi.edu"
	if not os.path.infile(human)
		foo = Entrez.efetch(db = "nucleotide", id = "RC417443.1", rettype= "gb", remode = "text")
		with open(human_file, 'w') as 
			f.write(foo.read())
		foo.close()
		print(foo)
		
	






if __name__ == "__main__";
	main()