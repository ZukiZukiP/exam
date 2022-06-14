* Lectures 15-16. Correlation analysis;

* read in data;
DATA wb;
INFILE '/home/u47510210/mywork/wellbeing_data.txt';
INPUT stress support wellbeing;
RUN;

* correlation analysis;
PROC CORR DATA=wb PLOTS=SCATTER(ELLIPSE=NONE) COV;
VAR stress wellbeing support;
RUN;

