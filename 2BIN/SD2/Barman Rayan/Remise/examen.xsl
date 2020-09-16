<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="html" version="html4.01" encoding="ISO-8859-1" />
	
	<xsl:template match="/">
		<html>
			<head>
				<title>Examens</title>
			</head>
			<body>
				<h1>Examens</h1>
				<hr/>
				<xsl:apply-templates select="//Local"></xsl:apply-templates>
			</body>
		</html>
	</xsl:template>
	
	<xsl:template match="Local">
		<xsl:variable name="LocalID" select="."></xsl:variable>
		<h2><xsl:value-of select="."/> 
		<xsl:choose>
			<xsl:when test="@nbPlace"> ( <xsl:value-of select="@nbPlace"/> ) </xsl:when>
			<xsl:otherwise> ( nombre de places inconnue)</xsl:otherwise>
		</xsl:choose>
		</h2>
		
		<ul>
		<xsl:apply-templates select="//Examen">
					<xsl:sort select="@date"/>	
					<xsl:with-param name="idLocal" select="."/>
		</xsl:apply-templates>
		</ul>
	</xsl:template>
	
	<xsl:template match="Examen">
		<xsl:param name="idLocal"/> 
		
		<xsl:apply-templates select="./Repartition"> 
			<xsl:with-param name="idLocalExamen" select="$idLocal"></xsl:with-param>
		</xsl:apply-templates>
	</xsl:template>
	
	<xsl:template match="Repartition">
		<xsl:param name="idLocalExamen"/>
		<xsl:if test="@local=$idLocalExamen">
			<li> <xsl:value-of select="../@date"></xsl:value-of>  <xsl:text>: </xsl:text>  <xsl:value-of select="../@nom"></xsl:value-of></li>
		</xsl:if>
	</xsl:template>
	
</xsl:stylesheet>