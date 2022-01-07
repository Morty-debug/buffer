#include <stdio.h>
#include <stdlib.h>
#include <NCore.h>
#include <NBiometricClient.h>
#include <NBiometrics.h>
#include <NMedia.h>
#include <NLicensing.h>

const NChar * defaultServerIp = N_T("127.0.0.1");
const NInt defaultAdminPort = 24932;
const NInt defaultPort = 25452;

int error = 0;

/*int bufftofile(char *buffer, //long size){
	 long size =464;
	//creamos el archivo
	FILE *f_dst = fopen("OUT", "wb");
	if(f_dst == NULL){
		printf("ERROR - No se pudo crear el archivo\n");
		return 1;
	}

	//escribimos en el archivo
	if(fwrite(buffer, 1, size, f_dst) != size){
		printf("ERROR - No se pudo crear el archivo\n");
		return 2;
	}

	//cerramos el archivo
	fclose(f_dst);
	f_dst = NULL;
	return 0;
}*/

int usage(){
	printf(N_T("usar:\n"));
	printf(N_T("\t./identificar.bin [template] [servidor] [puerto]\n"));
	printf(N_T("\n"));
	printf(N_T("\t[template] - template a enviar al servidor para ser identificado.\n"));
	printf(N_T("\t[servidor] - direccion ip del Mega Matcher. %s Por defecto\n"), defaultServerIp);
	printf(N_T("\t[puerto]   - puerto de comunicacion. %d Por defecto\n"), defaultAdminPort);
	return 1;
}
//464

NResult CreateSubject(HNSubject hSubject, const NChar * fileName){
	HNBuffer hBuffer = NULL;

	//HNBuffer hotroBuffer = NULL;
	//NSizeType size = 0;
	//unsigned  bytebuff[464];
	signed  bytebuff[464];
	void * bytebuffdoble;


	NResult result = N_OK;
	result = NFileReadAllBytesCN(fileName, &hBuffer);

	//bufftofile(hBuffer);

	if (NFailed(result)){ goto FINALLY; }
	result = NSubjectSetTemplateBuffer(hSubject, hBuffer);
	if (NFailed(result)){ goto FINALLY; }
	result = NSubjectSetId(hSubject, fileName);
	if (NFailed(result)){ goto FINALLY; }

	NSizeType sisa[5];
	result = NBufferGetSize(hBuffer, sisa);
	if (NFailed(result))
	{
		printf(N_T("SE JODIO\n"));
		goto FINALLY;
	}

	printf("%d %d %d",(int)sisa[0],sisa[1],sisa[3]);
	result = NBufferGetPtr(hBuffer, &bytebuffdoble);
	if (NFailed(result))
	{
		printf(N_T("SE JODIO :( BUU\n"));
		goto FINALLY;
	}

	


	//char *str = NULL;
	//char str[] = "This is tutorialspoint.com";
	//fp = fopen( "file.txt" , "w" );
//	printf("%d %d %d",sisa[0],sisa[1],sisa[3]);
    //fwrite(str , 1 , sizeof(str) , fp );
    //size_t fread(void *ptr, size_t size, size_t n, FILE *stream);
    //size_t fwrite(const void *ptr, size_t size, size_t n, FILE *stream);


	//unsigned char buffer[sizeof(int)];
	//result = NBufferCopyToPtr(hBuffer, str, sisa);
	/*NBufferToPtr(hBuffer,sisa,bytebuff);*/



	//NResult N_API NBufferGetPtr(HNBuffer hBuffer, void * * pValue);
	//NResult N_API NBufferGetSize(HNBuffer hBuffer, NSizeType * pValue);
	printf("\nOK\n");
	/*HNTemplate templateh =NULL;
	result = NSubjectGetTemplate(hSubject,&templateh);
	if (NFailed(result))
	{
		printf(N_T("NO no :(\n"));
		goto FINALLY;
	}*/
	

	//printf("%d %ld %lu",sisa,sisa,sisa);
result = NBufferCopyToPtr(hBuffer,bytebuff,sisa[0]);
	//result = NBufferToPtr(hBuffer,bytebuff[0],sisa[0]);
	if (NFailed(result))
	{
		printf(N_T("SE JODIO OTRAVEZ\n"));
		goto FINALLY;
	}

	char * b = (char *)&bytebuffdoble;
	FILE *fp = fopen( "BUFFERC.dat" , "w" );
	size_t size = 464;
    //fwrite(bytebuff , 1 , sisa , fp );
    if(fwrite(bytebuff, 1, sisa[0], fp) != sisa[0]){
		printf("ERROR - No se pudo crear el archivo\n");
		return 2;
	}
    fclose(fp);









	/*result = NBufferGetPtr(hBuffer,bytebuff);
	if (NFailed(result))
	{
		printf(N_T("SE JODIO\n"));
		goto FINALLY;
	}*/

	/*result = NSubjectGetTemplateBuffer(hSubject,&hotroBuffer);
	printf("aqui %d\n",result);
	if (NFailed(result)){ printf("ERRO1\n"); goto FINALLY; }
	
	result = NBufferToPtr(hotroBuffer,&size,buffer);
	printf("alla %d\n",result);
	if (NFailed(result)){ printf("ERRO2\n"); goto FINALLY; }*/


    HNBuffer hBufferr = NULL;
    HNSubject hSubjectO = NULL;
    result = NSubjectCreate(&hSubjectO);
	if (NFailed(result)){
		printf(N_T(":( No se logro crear subject\n"));
		error = 2;
		goto FINALLY;
	}

    result = NBufferCreateFromPtr(bytebuff,sisa[0],FALSE,&hBufferr);
	if (NFailed(result))
	{
		printf(N_T("SE JODIO :( NBufferCreateFromPtr \n"));
		goto FINALLY;
	}


	result = NSubjectSetTemplateBuffer(hSubjectO, hBufferr);
	if (NFailed(result))
	{
		printf(N_T("JODER :( NSubjectSetTemplateBuffer \n"));
		goto FINALLY;
	}

	result = NFileWriteAllBytesCN("BUFFERNEURO.dat", hBufferr);
	if (NFailed(result)){
		printf(N_T(":O :/\n"));
		error = 12;
		goto FINALLY;
	}



	return result;
FINALLY:
	{
		result = NObjectSet(NULL, &hBuffer);
		error = 3;
	}
	return result;
}

int main(int argc, NChar * * argv){
	HNBiometricClient hBiometricClient = NULL;
	HNSubject hSubject = NULL;
	HNClusterBiometricConnection hClusterBiometricConnection = NULL;
	HNBiometricTask hBiometricTask = NULL;
	HNString hHost = NULL;
	HNString hSubjectId = NULL;
	HNMatchingResult * hMatchingResults = NULL;
	NResult result = N_OK;
	int i;
	NInt resultsCount = 0;
	NInt score = 0;
	NClusterAddress clusterAddress;
	NBiometricStatus biometricStatus = nbsNone;
	const NChar * szSubjectId = NULL;
	const NChar * serverIp = defaultServerIp;
	NInt adminPort = defaultAdminPort;
	
	if (argc < 2){
		NCoreOnExitEx(NFalse);
		return usage();
	}
	
	result = NBiometricClientCreate(&hBiometricClient);
	if (NFailed(result)){
		printf(N_T("ERROR[001] No se logro crear cliente biometrico\n"));
		error = 1;
		goto FINALLY;
	}

	result = NSubjectCreate(&hSubject);
	if (NFailed(result)){
		printf(N_T("ERROR[002] No se logro crear subject\n"));
		error = 2;
		goto FINALLY;
	}

	result = CreateSubject(hSubject, argv[1]);
	if (NFailed(result)){
		printf(N_T("ERROR[003] No se logro leer o editar el template\n"));
		error = 3;
		goto FINALLY;
	}

	result = NClusterBiometricConnectionCreate(&hClusterBiometricConnection);
	if (NFailed(result)){
		printf(N_T("ERROR[004] No se logro crear la conexion\n"));
		error = 4;
		goto FINALLY;
	}

	if (argc == 3)
		serverIp = argv[2];

	if (argc == 4){
		serverIp = argv[2];
		adminPort = atoi(argv[3]);
	}

	result = NStringCreate(serverIp, &hHost);
	if (NFailed(result)){
		printf(N_T("ERROR[005] No se logro parsear la ip del servidor\n"));
		error = 5;
		goto FINALLY;
	}

	result = NClusterAddressCreateN(hHost, defaultPort, adminPort, &clusterAddress);
	if (NFailed(result)){
		printf(N_T("ERROR[006] No se logro establecer los parametros de conexion\n"));
		error = 6;
		goto FINALLY;
	}

	result = NClusterBiometricConnectionAddAddress(hClusterBiometricConnection, &clusterAddress, NULL);
	if (NFailed(result)){
		printf(N_T("ERROR[007] No se logro agregar los parametros de conexion a la conexion\n"));
		error = 7;
		goto FINALLY;
	}

	result = NBiometricClientAddRemoteConnection(hBiometricClient, hClusterBiometricConnection, NULL);
	if (NFailed(result)){
		printf(N_T("ERROR[008] No se logro agregar la conexion al cliente\n"));
		error = 8;
		goto FINALLY;
	}

	result = NBiometricEngineCreateTask(hBiometricClient, nboIdentify, hSubject, NULL, &hBiometricTask);
	if (NFailed(result)){
		printf(N_T("ERROR[009] No se logro crear la tarea de identificador\n"));
		error = 9;
		goto FINALLY;
	}

	result = NBiometricEnginePerformTask(hBiometricClient, hBiometricTask);
	if (NFailed(result)){
		printf(N_T("ERROR[010] No se logro ejecutar la tarea de enrrolamiento\n"));
		error = 10;
		goto FINALLY;
	}

	result = NBiometricTaskGetStatus(hBiometricTask, &biometricStatus);
	if (NFailed(result)){
		printf(N_T("ERROR[011] No se logro obtener estado de la tarea\n"));
		error = 11;
		goto FINALLY;
	}

	if (biometricStatus != nbsOk){
		if(biometricStatus == 610){
			printf(N_T("ERROR[610] Mega Matcher no logro Identificarlo, ninguna Coincidencia\n"));
			error = 610;
		}
		else{
			printf(N_T("ERROR[100] Mega Matcher no logro procesarlo\n"));
			error = 100;
		}
		goto FINALLY;
	}

	result = NSubjectGetMatchingResults(hSubject, &hMatchingResults, &resultsCount);
	if (NFailed(result)){
		printf(N_T("ERROR[012] No se logro obtener los resultados de Identificacion\n"));
		error = 12;
		goto FINALLY;
	}

	for (i = 0; i < resultsCount; i++){
		
		result = NStringSet(NULL, &hSubjectId);
		if (NFailed(result)){
			printf(N_T("ERROR[013] No se logro obtener el Subject ID\n"));
			error = 13;
			goto FINALLY;
		}

		result = NMatchingResultGetId(hMatchingResults[i], &hSubjectId);
		if (NFailed(result)){
			printf(N_T("ERROR[014] No se logro obtener el ID\n"));
			error = 14;
			goto FINALLY;
		}

		result = NStringGetBuffer(hSubjectId, NULL, &szSubjectId);
		if (NFailed(result)){
			printf(N_T("ERROR[015] No se logro parsear el ID\n"));
			error = 15;
			goto FINALLY;
		}

		result = NMatchingResultGetScore(hMatchingResults[i], &score);
		if (NFailed(result)){
			printf(N_T("ERROR[016] No se logro obtener la puntuacion de comparacion\n"));
			error = 16;
			goto FINALLY;
		}

		printf(N_T("ID: '%s' Puntuacion: %d\n"), szSubjectId, score);
	}
	
	if(error == 0){
		printf(N_T("%d\n"),error);
		NCoreOnExitEx(NFalse);
		return 0;
	}
	
FINALLY:
	{
		printf(N_T("ERROR\n"));
	}
	NCoreOnExitEx(NFalse);
	return 0;
}
