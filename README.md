# Planar

Planar geometry structures and transformations.

![Review](https://img.shields.io/github/actions/workflow/status/JoelLefkowitz/planar/review.yaml)
![Quality](https://img.shields.io/codacy/grade/_)

## Installing

```bash
conan search planar
```

You can also download the [sources](https://download-directory.github.io?url=https://github.com/JoelLefkowitz/planar/tree/master/src).

## Documentation

Documentation and more detailed examples are hosted on [Github Pages](https://joellefkowitz.github.io/planar).

## Tooling

### Dependencies

To install dependencies:

```bash
yarn install
pip install .[all]
conan install .
```

### Tests

To run tests:

```bash
scons test
```

### Documentation

To generate the documentation locally:

```bash
scons docs
```

### Linters

To run linters:

```bash
scons lint
```

### Formatters

To run formatters:

```bash
scons format
```

### Publishing

The [ConanCenter](https://conan.io/center) doesn't yet allow users to publish packages independently. Package recipes are submitted to the [conan-center-index](https://github.com/conan-io/conan-center-index). A copy of this recipe is kept in this repository in the `publish` folder. This allows us to test that the recipe is compatible with new versions and makes it easier to submit updates to the conan-center-index.

To test the recipe can build the latest published tag:

```bash
conan create publish/all/conanfile.py --version $(yq -r ".versions | keys | .[0]" publish/config.yml)
```

This will fetch the sources and create a locally cached version of the package. This version can also be published to a local remote for testing:

```bash
conan upload <package>/<version> -r <remote>
```

### Toolchains

Scripts are defined in the `scripts` folder and can be invoked with `toolchains`:

To generate header guards:

```bash
npx toolchains guards
```

## Contributing

Please read this repository's [Code of Conduct](CODE_OF_CONDUCT.md) which outlines our collaboration standards and the [Changelog](CHANGELOG.md) for details on breaking changes that have been made.

This repository adheres to semantic versioning standards. For more information on semantic versioning visit [SemVer](https://semver.org).

Bump2version is used to version and tag changes. For example:

```bash
bump2version patch
```

### Contributors

- [Joel Lefkowitz](https://github.com/joellefkowitz) - Initial work

## Remarks

Lots of love to the open source community!

<div align='center'>
    <img width=200 height=200 src='https://media.giphy.com/media/osAcIGTSyeovPq6Xph/giphy.gif' alt='Be kind to your mind' />
    <img width=200 height=200 src='https://media.giphy.com/media/KEAAbQ5clGWJwuJuZB/giphy.gif' alt='Love each other' />
    <img width=200 height=200 src='https://media.giphy.com/media/WRWykrFkxJA6JJuTvc/giphy.gif' alt="It's ok to have a bad day" />
</div>
