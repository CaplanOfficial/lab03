#ifndef WAV_CORE_H
#define WAV_CORE_H
#include<exception>
#include<fstream>

#include "wav_header.h"

// Possible errors
class IO_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "IO_ERROR\n";
	};
};
class BAD_PARAMS : public std::exception {
	virtual const char* what() const throw() {
		return "BAD_PARAMS\n";
	};
};
class BAD_FORMAT : public std::exception {
	virtual const char* what() const throw() {
		return "BAD_FORMAT\n";
	};
};
class UNSUPPORTED_FORMAT : public std::exception {
	virtual const char* what() const throw() {
		return "UNSUPPORTED_FORMAT: Only 16-bit samples is supported\n";
	};
};


//HEADER
class HEADER_RIFF_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_RIFF_ERROR\n";
	};
};
class HEADER_FILE_SIZE_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_FILE_SIZE_ERROR\n";
	};
};
class HEADER_WAVE_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_WAVE_ERROR\n";
	};
};
class HEADER_FMT_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_FMT_ERROR\n";
	};
};
class HEADER_NOT_PCM : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_NOT_PCM\n";
	};
};
class HEADER_SUBCHUNK1_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_SUBCHUNK1_ERROR\n";
	};
};
class HEADER_BYTES_RATE_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_BYTES_RATE_ERROR\n";
	};
};
class HEADER_BLOCK_ALIGN_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return "HEADER_BLOCK_ALIGN_ERROR\n";
	};
};
class  HEADER_SUBCHUNK2_SIZE_ERROR : public std::exception {
	virtual const char* what() const throw() {
		return " HEADER_SUBCHUNK2_SIZE_ERROR\n";
	};
};


// ************************************************************************
// * Functions for working with WAV file
// ************************************************************************

// Reads file 'filename' and puts header's data to 'header_ptr' address.
// Also checks header validity, returns 'WAV_OK' on success.
wav_errors_e read_header( const char* filename, wav_header_s* header_ptr );

// Prints header's data from 'header_ptr' address.
void print_info( const wav_header_s* header_ptr );

// Reads file 'filename' and puts PCM data (raw sound data) to 'channels_data'.
// Also checks header validity, returns 'WAV_OK' on success.
wav_errors_e extract_data_int16( const char* filename, std::vector<std::vector<short>>& channels_data );


// Creates a new WAV file 'filename', using 'sample_rate' and PCM data from 'channels_data'.
// Returns 'WAV_OK' on success.
wav_errors_e make_wav_file( const char* filename, int sample_rate, const std::vector<std::vector<short>>& channels_data );


// ************************************************************************
// * Functions for working with sound PCM data - Digital Signal Processing
// ************************************************************************

// Makes mono PCM data from stereo 'source'.
// Returns 'WAV_OK' on success.
wav_errors_e make_mono( const std::vector<std::vector<short>>& source, std::vector<std::vector<short>>& dest_mono );

// Adds a reverberation (it's like an echo).
// Returns 'WAV_OK' on success.
wav_errors_e make_reverb(std::vector<std::vector<short>>& sounds, int sample_rate , double delay_seconds, float decay);


// ************************************************************************
// * Private functions
// ************************************************************************

// Fills header with zeroes.
void null_header( wav_header_s* header_ptr );

// Checks header validity.
// Returns 'WAV_OK' on success.
wav_headers_errors_e check_header( const wav_header_s* header_ptr, size_t file_size_bytes );

// Fills header information, using input parameters. This function calls prefill_header() itself.
wav_errors_e fill_header( wav_header_s* header_ptr, int chan_count, int bits_per_sample, int sample_rate, int samples_count_per_chan );

// Fills 'header_ptr' with default values.
void prefill_header( wav_header_s* header_ptr );


#endif // WAV_CORE_H
