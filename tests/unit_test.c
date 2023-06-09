#include <criterion/criterion.h>
#include <criterion/internal/test.h>
#include <criterion/new/assert.h>
#include <criterion/internal/assert.h>
#include "../include/network.h"

Test(create_server, invalid_server_port)
{
    server_t *serv = create_server(-123);
    cr_assert_null(serv);
}

Test(create_server, valid_server_port)
{
    server_t *serv = create_server(1234);
    cr_assert_not_null(serv);
    free(serv);
}
