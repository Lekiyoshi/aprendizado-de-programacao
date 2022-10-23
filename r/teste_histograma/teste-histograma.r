dados <- c(32.46, 32.61, 32.65, 32.65, 32.65, 32.86, 32.86, 32.90, 32.98, 33.01, 33.04, 
       33.08, 33.13, 33.13, 33.15, 33.25, 33.28, 33.38, 33.45, 33.52, 33.75, 33.76, 
       34.05, 34.13, 34.39, 34.55, 34.66, 34.67, 34.67, 34.91, 35.14, 35.19, 35.20, 
       35.32, 35.51, 35.55, 35.68, 35.76, 35.97, 36.16, 36.21, 36.41, 37.10, 37.79, 
       38.98, 39.63, 39.97, 41.05, 41.47, 41.74, 41.82, 42.81, 42.99, 43.20, 44.10)

hist(dados,
	main = "Histograma de Distribuição de Cotações",
	xlab = "Cotação",
	ylab = "Frequência"
	include.lowest = TRUE,
	right = TRUE,
	xlim = c(32, 46),
	ylim = c(0, 30),
	labels = TRUE)
