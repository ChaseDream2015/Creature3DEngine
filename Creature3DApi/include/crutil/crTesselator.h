/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
#ifndef CRUTIL_Tesselator
#define CRUTIL_Tesselator

#include <CRCore/crGeometry.h>

#include <CRUtil/crExport.h>

#include <crgl/glu.h>

#include <vector>

/* Win32 calling conventions. (or a least thats what the GLUT example tess.c uses.)*/
#ifndef CALLBACK
#define CALLBACK
#endif


namespace CRUtil {

/** Originally a simple class for tessellating a single polygon boundary.
  * Using old style glu tessellation functions for portability.
  * Upgraded Jan 2004 to use the modern glu tessellation functions.*/

class CRUTIL_EXPORT crTesselator : public CRCore::Referenced
{
    public:
   
        crTesselator();
        ~crTesselator();

        /** The winding rule, see red book ch 11. */
        enum WindingType{
            TESS_WINDING_ODD          = GLU_TESS_WINDING_ODD,
            TESS_WINDING_NONZERO      = GLU_TESS_WINDING_NONZERO     ,
            TESS_WINDING_POSITIVE     = GLU_TESS_WINDING_POSITIVE    ,
            TESS_WINDING_NEGATIVE     = GLU_TESS_WINDING_NEGATIVE    ,
            TESS_WINDING_ABS_GEQ_TWO  =    GLU_TESS_WINDING_ABS_GEQ_TWO
        } ;

        /** we interpret all contours in the geometry as a single set to be tesselated or
         * each separate drawable's contours needs to be tesselated. */
        enum TesselationType {
            TESS_TYPE_GEOMETRY, // tesselate everything in the geometry object
            TESS_TYPE_DRAWABLE, // tesselate each polygon, triangles & quads drawables in geometry separately
            TESS_TYPE_POLYGONS // tesselate ONLY polygon drawables in geometry separately
        };

        /** Set and get tesselation request boundary only on/off */
        void setBoundaryOnly (const bool tt) { m_boundaryOnly=tt;}
        inline const bool getBoundaryOnly ( ) { return m_boundaryOnly;}

        /** Set and get tesselation windong rule */
        void setWindingType (const WindingType wt) { m_wtype=wt;}
        inline const WindingType getWindingType ( ) { return m_wtype;}

        /** Set and get tesselation type */
        void setTesselationType (const TesselationType tt) { m_ttype=tt;}
        inline const TesselationType getTesselationType ( ) { return m_ttype;}

        /** Change the contours lists of the geometry into tesselated primitives (the
          * list of primitives in the original geometry is stored in the tesselator for
          * possible re-use. 
          * The name remains retesselatePolygons although it now handles trifans, strips, quads etc.
          * as well as Polygons so as to not break old codes relying on this function name. */
        void retesselatePolygons(CRCore::crGeometry &cxgeom);

        CRCore::crGeometry::PrimitiveList  getContours() { return m_Contours;}

        typedef std::vector<CRCore::crVector3*> VertexPointList;
        
        struct Prim : public CRCore::Referenced
        {
            Prim(GLenum mode):m_mode(mode) {}
        
            typedef std::vector<CRCore::crVector3*> VecList;

            GLenum  m_mode;
            VecList m_vertices;
        };
        
        void beginTesselation();
        
        void beginContour();
        void addVertex(CRCore::crVector3* vertex);
        void endContour();
        
        void endTesselation();

        typedef std::vector< CRCore::ref_ptr<Prim> > PrimList;
        
        PrimList& getPrimList() { return m_primList; }        
        
        void reset();
        
    protected:

        /** remove unused parts of the array, eg for wehn retesselating
         * tesselation can introduce extra vertices for concave or crossing boundaries,
         * these will leak memory if not removed when retesselating. */
        void reduceArray(CRCore::Array * cold, const unsigned int nnu);

        void collectTesselation(CRCore::crGeometry &cxgeom);
        
        typedef std::map<CRCore::crVector3*,unsigned int> VertexPtrToIndexMap;
        void addContour(CRCore::crPrimitive* primitive, CRCore::Vec3Array* vertices);
        void handleNewVertices(CRCore::crGeometry& geom,VertexPtrToIndexMap &vertexPtrToIndexMap);

        void begin(GLenum mode);
        void vertex(CRCore::crVector3* vertex);
        void combine(CRCore::crVector3* vertex,void* vertex_data[4],GLfloat weight[4]);
        void end();
        void error(GLenum errorCode);

    
		static void CALLBACK edgeFlagCallback(bool flag);
        static void CALLBACK beginCallback(GLenum which, void* userData);
        static void CALLBACK vertexCallback(GLvoid *data, void* userData);
        static void CALLBACK combineCallback(GLdouble coords[3], void* vertex_data[4],
                              GLfloat weight[4], void** outData,
                              void* useData);
        static void CALLBACK endCallback(void* userData);
        static void CALLBACK errorCallback(GLenum errorCode, void* userData);
        
        
        struct Vec3d
        {
            double _v[3];
        };


        struct NewVertex
        {
        
            NewVertex():
                _vpos(0),
                _f1(0),
                _v1(0),
                _f2(0),
                _v2(0),
                _f3(0),
                _v3(0),
                _f4(0),
                _v4(0) {}
            
            NewVertex(const NewVertex& nv):
                _vpos(nv._vpos),
                _f1(nv._f1),
                _v1(nv._v1),
                _f2(nv._f2),
                _v2(nv._v2),
                _f3(nv._f3),
                _v3(nv._v3),
                _f4(nv._f4),
                _v4(nv._v4) {}

            NewVertex(CRCore::crVector3* vx,
                      float f1,CRCore::crVector3* v1,
                      float f2,CRCore::crVector3* v2,
                      float f3,CRCore::crVector3* v3,
                      float f4,CRCore::crVector3* v4):
                _vpos(vx),
                _f1(f1),
                _v1(v1),
                _f2(f2),
                _v2(v2),
                _f3(f3),
                _v3(v3),
                _f4(f4),
                _v4(v4) {}

            CRCore::crVector3  *_vpos; // added gwm Jan 2004 the vertex coords s.t. NewVertex can be used in a std::vector
        
            float       _f1;
            CRCore::crVector3*  _v1;

            float       _f2;
            CRCore::crVector3*  _v2;

            float       _f3;
            CRCore::crVector3*  _v3;

            float       _f4;
            CRCore::crVector3*  _v4;
            
        };
        
        //change NewVertexList from std::map<CRCore::crVector3*,NewVertex> NewVertexList;
        // because this has undefined order of insertion for new vertices. 
        // which occasionally corrupted the texture mapping.
        typedef std::vector<NewVertex> NewVertexList;
        typedef std::vector<Vec3d*> Vec3dList;

        GLUtesselator*  m_tobj;
        PrimList        m_primList;
        Vec3dList       m_coordData;
        NewVertexList   m_newVertexList;
        GLenum          m_errorCode;

        /** winding rule, which parts will become solid */
        WindingType m_wtype; 

        /** tesselation rule, which parts will become solid */
        TesselationType m_ttype;

        bool m_boundaryOnly; // see gluTessProperty - if true: make the boundary edges only.

        /** number of vertices that are part of the 'original' set of contours */
        unsigned int m_numberVerts;

        /** List of primitives that define the contours */
        CRCore::crGeometry::PrimitiveList                m_Contours;

        /** count number of primitives in a geometry to get right no. of norms/colurs etc for per_primitive attributes. */
        unsigned int m_index;
};

}

#endif
