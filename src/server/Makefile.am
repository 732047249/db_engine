AUTOMAKE_OPTIONS = foreign subdir-objects

top_dir = ${top_srcdir}/..
proj_dir = ${top_srcdir}/src
server_rootdir = ${top_srcdir}/src/server
third_dir = ${top_dir}/third-64
pub_dir = ${top_dir}/pub_util

AM_CPPFLAGS = -I${proj_dir} \
			  -I${proj_dir}/rpc/ \
		      -I${third_dir}/protobuf/include/ \
		      -I${third_dir}/boost/include/ \
		      -I${third_dir}/glog/include/ \
		      -I${third_dir}/libev/include/ \
		      -I${third_dir}/iniparser/include/ \
		      -I${third_dir}/leveldb/include/ \
		      -I${pub_dir}

#AM_LDFLAGS = -lz -lrt -lm -lpthread -rdynamic
AM_LDFLAGS = -lz -lrt -lm -lpthread -lstdc++

LDADD = ${proj_dir}/rpc/rpc_server/librpc_server.a \
        ${proj_dir}/common/libcommon.a \
	    ${proj_dir}/engine_db/libdb.a \
	    ${proj_dir}/proto/libproto.a \
	    ${third_dir}/libev/lib/*.a \
	    ${third_dir}/protobuf/lib/*.a \
	    ${third_dir}/boost/lib/*.a \
	    ${third_dir}/glog/lib/*.a \
	    ${third_dir}/iniparser/lib/*.a \
	    ${third_dir}/leveldb/lib/*.a


SERVER_SRC= ${server_rootdir}/db_server.cc \
		    ${server_rootdir}/db_service.h \
		    ${server_rootdir}/db_service.cpp 

bin_PROGRAMS = db_server

db_server_SOURCES = ${SERVER_SRC}

