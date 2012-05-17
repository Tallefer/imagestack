/*
 * Copyright (c) 2003, 2007-8 Matteo Frigo
 * Copyright (c) 2003, 2007-8 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "api.h"
#include "rdft.h"

X(plan) XGURU(split_dft_c2r)(int rank, const IODIM *dims,
                             int howmany_rank, const IODIM *howmany_dims,
                             R *ri, R *ii, R *out, unsigned flags) {
    if (!GURU_KOSHERP(rank, dims, howmany_rank, howmany_dims)) { return 0; }

    if (out != ri) {
        flags |= FFTW_DESTROY_INPUT;
    }
    return X(mkapiplan)(
               0, flags,
               X(mkproblem_rdft2_d_3pointers)(
                   MKTENSOR_IODIMS(rank, dims, 1, 1),
                   MKTENSOR_IODIMS(howmany_rank, howmany_dims, 1, 1),
                   TAINT_UNALIGNED(out, flags),
                   TAINT_UNALIGNED(ri, flags),
                   TAINT_UNALIGNED(ii, flags), HC2R));
}