#include "userdiff.h"
static int diff_suppress_blank_empty;
static int diff_mnemonic_prefix;
static void diff_filespec_load_driver(struct diff_filespec *one);
static char *run_textconv(const char *, struct diff_filespec *, size_t *);

	if (!strcmp(var, "diff.mnemonicprefix")) {
		diff_mnemonic_prefix = git_config_bool(var, value);
		return 0;
	}
	switch (userdiff_config_porcelain(var, value)) {
		case 0: break;
		case -1: return -1;
		default: return 0;
	/* like GNU diff's --suppress-blank-empty option  */
	if (!strcmp(var, "diff.suppress-blank-empty")) {
		diff_suppress_blank_empty = git_config_bool(var, value);
		return 0;
	}

	switch (userdiff_config_basic(var, value)) {
		case 0: break;
		case -1: return -1;
		default: return 0;
	struct strbuf res = STRBUF_INIT;
	const char *a_prefix, *b_prefix;

	if (diff_mnemonic_prefix && DIFF_OPT_TST(o, REVERSE_DIFF)) {
		a_prefix = o->b_prefix;
		b_prefix = o->a_prefix;
	} else {
		a_prefix = o->a_prefix;
		b_prefix = o->b_prefix;
	}
	quote_two_c_style(&a_name, a_prefix, name_a, 0);
	quote_two_c_style(&b_name, b_prefix, name_b, 0);

	diff_filespec_load_driver(one);
	if (one->driver->textconv) {
		size_t size;
		mf->ptr = run_textconv(one->driver->textconv, one, &size);
		if (!mf->ptr)
			return -1;
		mf->size = size;
	}
	else {
		mf->ptr = one->data;
		mf->size = one->size;
	}
	xdi_diff_outf(&minus, &plus, fn_out_diff_words_aux, diff_words,
		      &xpp, &xecfg, &ecb);
	if (diff_suppress_blank_empty
	    && len == 2 && line[0] == ' ' && line[1] == '\n') {
		line[0] = '\n';
		len = 1;
	}

	struct strbuf name = STRBUF_INIT;
		struct strbuf buf = STRBUF_INIT;
		 * made to the preimage. In --dirstat-by-file mode, count
		 * damaged files, not damaged lines. This is done by
		 * counting only a single damaged line per file.
		if (DIFF_OPT_TST(options, DIRSTAT_BY_FILE) && damage > 0)
			damage = 1;
void diff_filespec_load_driver(struct diff_filespec *one)
	if (!one->driver)
		one->driver = userdiff_find_by_path(one->path);
	if (!one->driver)
		one->driver = userdiff_find_by_name("default");
int diff_filespec_is_binary(struct diff_filespec *one)
	if (one->is_binary == -1) {
		diff_filespec_load_driver(one);
		if (one->driver->binary != -1)
			one->is_binary = one->driver->binary;
		else {
			if (!one->data && DIFF_FILE_VALID(one))
				diff_populate_filespec(one, 0);
			if (one->data)
				one->is_binary = buffer_is_binary(one->data,
						one->size);
			if (one->is_binary == -1)
				one->is_binary = 0;
		}
	return one->is_binary;
static const struct userdiff_funcname *diff_funcname_pattern(struct diff_filespec *one)
	diff_filespec_load_driver(one);
	return one->driver->funcname.pattern ? &one->driver->funcname : NULL;
void diff_set_mnemonic_prefix(struct diff_options *options, const char *a, const char *b)
	if (!options->a_prefix)
		options->a_prefix = a;
	if (!options->b_prefix)
		options->b_prefix = b;
	const char *a_prefix, *b_prefix;

	diff_set_mnemonic_prefix(o, "a/", "b/");
	if (DIFF_OPT_TST(o, REVERSE_DIFF)) {
		a_prefix = o->b_prefix;
		b_prefix = o->a_prefix;
	} else {
		a_prefix = o->a_prefix;
		b_prefix = o->b_prefix;
	}
	a_one = quote_two(a_prefix, name_a + (*name_a == '/'));
	b_two = quote_two(b_prefix, name_b + (*name_b == '/'));
		const struct userdiff_funcname *pe;
		xdi_diff_outf(&mf1, &mf2, fn_out_consume, &ecbdata,
			      &xpp, &xecfg, &ecb);
		xdi_diff_outf(&mf1, &mf2, diffstat_consume, diffstat,
			      &xpp, &xecfg, &ecb);
		xdi_diff_outf(&mf1, &mf2, checkdiff_consume, &data,
			      &xpp, &xecfg, &ecb);
	spec->is_binary = -1;
	struct strbuf buf = STRBUF_INIT;
		struct strbuf buf = STRBUF_INIT;
		struct userdiff_driver *drv = userdiff_find_by_path(attr_path);
		if (drv && drv->external)
			pgm = drv->external;
	if (!diff_mnemonic_prefix) {
		options->a_prefix = "a/";
		options->b_prefix = "b/";
	}
	} else if (opt_arg(arg, 0, "dirstat-by-file",
			   &options->dirstat_percent)) {
		options->output_format |= DIFF_FORMAT_DIRSTAT;
		DIFF_OPT_SET(options, DIRSTAT_BY_FILE);
	git_SHA_CTX *ctx;
	git_SHA1_Update(data->ctx, line, new_len);
	git_SHA_CTX ctx;
	git_SHA1_Init(&ctx);
		git_SHA1_Update(&ctx, buffer, len1);
		xdi_diff_outf(&mf1, &mf2, patch_id_consume, &data,
			      &xpp, &xecfg, &ecb);
	git_SHA1_Final(sha1, &ctx);

static char *run_textconv(const char *pgm, struct diff_filespec *spec,
		size_t *outsize)
{
	struct diff_tempfile temp;
	const char *argv[3];
	const char **arg = argv;
	struct child_process child;
	struct strbuf buf = STRBUF_INIT;

	prepare_temp_file(spec->path, &temp, spec);
	*arg++ = pgm;
	*arg++ = temp.name;
	*arg = NULL;

	memset(&child, 0, sizeof(child));
	child.argv = argv;
	child.out = -1;
	if (start_command(&child) != 0 ||
	    strbuf_read(&buf, child.out, 0) < 0 ||
	    finish_command(&child) != 0) {
		if (temp.name == temp.tmp_path)
			unlink(temp.name);
		error("error running textconv command '%s'", pgm);
		return NULL;
	}
	if (temp.name == temp.tmp_path)
		unlink(temp.name);

	return strbuf_detach(&buf, outsize);
}