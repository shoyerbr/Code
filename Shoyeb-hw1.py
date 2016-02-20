from Bio import Entrez
from Bio import SeqIO
from Bio.SubsMat import MatrixInfo
import os.path 
import sys
#the match score MATCH, mismatch 
#score MISMATCH and the DNA gap penalty DGAP, 
#and the protein gap penalty PGAP
def Allign(seq1, seq2, match, mismatch, gap, blos):
	blosum_matrix = MatrixInfo.blosum62
	score = 0
	num_matches = 0
	if blos == 0:
		seq1 = ' ' + seq1
		seq2 = ' ' + seq2
	size1 = len(seq1)
	size2 = len(seq2)
	scoring_matrix = [[0 for x in range(size2)] for x in range(size1)]
	direction_matrix = [[0 for x in range(size2)] for x in range(size1)]
	scoring_matrix[0][0] = 0
	for i in range(1,size1):
		scoring_matrix[i][0] = scoring_matrix[i-1][0] + gap
		direction_matrix[i][0] = 1 
	for i in range(1,size2):
		scoring_matrix[0][i] = scoring_matrix[0][i-1] + gap
		direction_matrix[0][i] = 3
	for i in range(1,size2):
		for j in range(1,size1):
			temp_score  = mismatch
			if seq1[j] == seq2[i] and  blos == 0:
				temp_score = match
			if (blos == 1):
				temp_s1 = seq1[j]
				temp_s2 = seq2[i]
				try:
					temp_score = blosum_matrix[temp_s1,temp_s2]
				except:
					temp_score = blosum_matrix[temp_s2,temp_s1]
			big = scoring_matrix[j-1][i-1] + temp_score
			direction_matrix[j][i] = 2
			if big < (scoring_matrix[j][i-1] + gap):
				big = (scoring_matrix[j][i-1] + gap)
				direction_matrix[j][i] = 3
			if big < (scoring_matrix[j-1][i] + gap):
				big = (scoring_matrix[j-1][i] + gap)
				direction_matrix[j][i] = 1
			scoring_matrix[j][i] = big
	startx = size1-1
	starty = size2-1
	new_seq1 = ''
	new_seq2 = ''
	middle = ''
	leng = 0
	while startx != 0:
		leng += 1
		if (direction_matrix[startx][starty] == 2):
			new_seq1 = seq1[startx] + new_seq1
			new_seq2 = seq2[starty] + new_seq2
			if seq1[startx] == seq2[starty]:
				middle = "|" + middle
				num_matches += 1
			else:
				middle = " " + middle
			startx -= 1
			starty -= 1
		elif (direction_matrix[startx][starty] == 1):
			new_seq1 = seq1[startx] + new_seq1
			new_seq2 = '-' + new_seq2
			middle = ' ' + middle
			startx -= 1
		elif (direction_matrix[startx][starty] == 3):
			new_seq1 = '-' + new_seq1
			new_seq2 = seq2[starty] + new_seq2	
			middle = ' ' + middle
			starty -= 1
	print(new_seq1)
	print(middle)
	print(new_seq2)
	print("Best Global Alignment: score= " + str(scoring_matrix[size1-1][size2-1]) + "  len= " + str(leng) + "  matches = " + str(num_matches))
	return scoring_matrix[size1-1][size2-1]
def main():
	human = './KC417443.1.gb'
	human_file = 'KC417443.1.gb'
	match_score = int(sys.argv[1])
	mismatch_score = int(sys.argv[2])
	DNA_gap_penalty = int(sys.argv[3])
	Protein_gap_penalty = int(sys.argv[4])
		
	Entrez.email = "shoyeb@rpi.edu"
	foo = ''
	#number = Allign('ACAGTAG', 'ACTCG', 1, 0, -1)
	#print(number)
	if not os.path.isfile(human):
		foo = Entrez.efetch(db = "nucleotide", id = "KC417443.1", rettype= "gb", remode = "text")
		with open(human_file, 'w') as f: 
			f.write(foo.read())
		foo.close()
	sequence1 = ''
	sequence2 = ''
	for genome in SeqIO.parse(human_file, 'genbank'):
		for gene in genome.features:
			if (gene.type == 'CDS') and 'cox1' in gene.qualifiers['gene'][0].lower():
				sequence1 = gene.qualifiers['translation']
				sequence2 = gene.extract(genome.seq)
	cyano = './CP000576.1.gb'
	cyano_file = 'CP000576.1.gb'	
	sequence3 = ''
	sequence4 = ''
	if not os.path.isfile(cyano):
		foo2 = Entrez.efetch(db = "nucleotide", id = "CP000576.1", rettype= "gb", remode = "text")
		with open(cyano_file, 'w') as f: 
			f.write(foo2.read())
		foo2.close()
	for genome in SeqIO.parse(cyano_file, 'genbank'):
		for gene in genome.features:
			if 'gene' not in gene.qualifiers:
				continue
			if (gene.type == 'CDS') and 'cyob' in gene.qualifiers['gene'][0].lower():
				sequence3 = gene.qualifiers['translation']
				sequence4 = gene.extract(genome.seq)	
	Allign(sequence2, sequence4, match_score, mismatch_score, DNA_gap_penalty, 0)
	protein1 = ''
	protein2 = ''
	for i in range(0,len(sequence1)):
		protein1 += sequence1[i]
	for i in range(0,len(sequence3)):
		protein2 += sequence3[i]	
	Allign(protein1, protein2, match_score, mismatch_score, Protein_gap_penalty, 1)
if __name__ == "__main__":
	main()