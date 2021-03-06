<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<!-- Author Barman Rayan -->
	<xsl:output method="html" version="html4.01" encoding="ISO-8859-1" />
	<xsl:template match="/">
		<html>
			<head>
				<title>Mes Recettes</title>
				<meta name="author" content="Barman Rayan"/>
			</head>
			<body>
				<p>Ce recueil comprend actuellement 
				<xsl:value-of select="count(//recette)"/> <!-- compte le nombre d'occurence du nombre de noeud recette-->
				recettes : </p>
				<ul>
					<!-- boucle sur le nombre de noeud recette -->
					<xsl:for-each select="//recette">
						<xsl:sort select="@type"/>
						<xsl:sort select=".//titre"/>
					<li>
						<!-- ajoute element html avec attribut href qui contient notre position-->
						<xsl:element name="a"> 
							<xsl:attribute name="href">#recette_<xsl:value-of select="position()"/>
							</xsl:attribute>
							<xsl:value-of select=".//titre"/>
						</xsl:element>
					</li>
					</xsl:for-each>
				</ul>
				<xsl:apply-templates select="//recette">
					<xsl:sort select="@type"/>
					<xsl:sort select=".//titre"/>
				</xsl:apply-templates>
			</body>
		</html>
	</xsl:template>
	
	<xsl:template match="titre">
		<xsl:value-of select="."/>
	</xsl:template>
	
	<xsl:template match="recette">
	
		<xsl:element name="h1">
			<xsl:attribute name="id">recette_<xsl:value-of select="position()"/> </xsl:attribute>
		</xsl:element>
		
		<h1> <xsl:value-of select="position()"/>. <xsl:value-of select="./entete/titre"/> </h1>
		
		<xsl:element name="div">
			<xsl:attribute name="style">
				color:blue;text-align:right;font-style: italic;margin:20px
			</xsl:attribute>
			<xsl:apply-templates select="./entete/remarque"></xsl:apply-templates>
			<xsl:apply-templates select="./entete/preparation"></xsl:apply-templates>
			<xsl:apply-templates select="./entete/cuisson"></xsl:apply-templates>
			<xsl:apply-templates select="./entete/marinade"></xsl:apply-templates>
		</xsl:element>
		
		<xsl:apply-templates select="./ingredients"></xsl:apply-templates>
		<h3> Procédure</h3>
		<ol>
			<xsl:apply-templates select="./instruction"></xsl:apply-templates>
		</ol>	
	</xsl:template>
	
	<xsl:template match="ingredients">
		<h3> Ingredients 
		<xsl:choose>
			<xsl:when test="@pour">
				(pour <xsl:value-of select="@pour"></xsl:value-of> )
			</xsl:when>
			<xsl:otherwise></xsl:otherwise>
		</xsl:choose>
		</h3>
		<ul>
			<xsl:apply-templates select="./ingredient">
				<xsl:sort select="."/>
			</xsl:apply-templates>
		</ul>
	</xsl:template>
	
	<xsl:template match="entete">
	</xsl:template>
	
	<xsl:template match="preparation">
		Temps de préparation : <xsl:value-of select="."/>
		<br></br>
	</xsl:template>
	
	<xsl:template match="cuisson">
		Temps de cuisson : <xsl:value-of select="."/>
		<br></br>
	</xsl:template>
	
	<xsl:template match="marinade">
		Temps de marinade : <xsl:value-of select="."/>
		<br></br>
	</xsl:template>
	
	<xsl:template match="remarque">
		<xsl:element name="p">
			<xsl:attribute name="style">color:navy;text-align:left</xsl:attribute>
			<xsl:value-of select="."/>
		</xsl:element>
	</xsl:template>
	
	<xsl:template match="ingredient">
		<li>
			<xsl:value-of select="@qte"/>
				<xsl:text> </xsl:text> <!-- Permet de mettre un espace -->
			<xsl:value-of select="@unite"/> 
				<xsl:text> </xsl:text>    
			<xsl:value-of select="."/> 
		</li>
	</xsl:template>
	
	<xsl:template match="instruction">
		<li>
			<xsl:value-of select="."/>
		</li>
	</xsl:template>
	
</xsl:stylesheet>