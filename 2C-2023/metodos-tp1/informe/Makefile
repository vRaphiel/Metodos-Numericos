all:
	pdflatex --shell-escape -interaction=batchmode -synctex=1 main
	bibtex main
	pdflatex --shell-escape -interaction=batchmode -synctex=1 main
	pdflatex --shell-escape -interaction=batchmode -synctex=1 main

clean:
	rm *.aux *.log *.out *.toc *.synctex.gz *.fls *.blg *.fdb_latexmk *.bbl